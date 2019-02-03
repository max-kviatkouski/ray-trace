#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"
#include <cmath>
#include "Vec3d.h"
#include "Sphere.h"
#include <vector>
#include <array>

double get_distance_to_plane(int fov, int plane_width);

//nX, nY, nZ
//nZ is a vector opposite to the view ray by definition
//nX is orthogonal to nZ and parallel to XoZ plane
//nY is orthogonal to nZ and parallel to YoZ plane
//all vectors have length of 1 (pixel) making them basis vectors for the view plane
std::vector<Vec3d> get_norm_vectors(Vec3d v);

//calculate normalized ray vector corresponding to a pixel with coordinates (x, y)
Vec3d vector_for_plane_pixel(int _x, int _y, int width, int height, std::vector<Vec3d> norms, double d);

RgbColor generate_gradient(int x, int y, int WIDTH, int HEIGHT);

void save_image(const char *filename, int WIDTH, int HEIGHT, std::vector<RgbColor> image);

const int MAX_CHANNEL = 255;

int main() {
    //field of view
    const unsigned int FOV = 90;
    Vec3d VIEW_RAY = Vec3d(0.0, 0.0, -1.0);
    Vec3d VIEW_POS = Vec3d(0.0, 0.0, 0.0);
    const int HEIGHT = 600;
    const int WIDTH = 900;

    std::vector<RgbColor> image(WIDTH * HEIGHT);
    std::vector<Sphere> scene = {
            Sphere(Vec3d(0, 0, -600), 100.0, RgbColor(200, 0, 0)),
            Sphere(Vec3d(150, 0, -500), 50.0, RgbColor(100, 18, 10)),
            Sphere(Vec3d(0, 0, -550), 75.0, RgbColor(100, 18, 180))
    };

    const char *filename = "test.png";
    std::vector<Vec3d> norms = get_norm_vectors(VIEW_RAY);
    double const DISTANCE = get_distance_to_plane(FOV, WIDTH);

    ////RENDERING PART
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::vector<Sphere>::iterator it;
            double min_dist = -1.0;
            RgbColor color;
            for (it = scene.begin(); it != scene.end(); it++) {
                Sphere s = *it;
                double dist;
                if (s.intersect(VIEW_POS, vector_for_plane_pixel(j, i, WIDTH, HEIGHT, norms, DISTANCE), dist)) {
                    if (min_dist < 0 || dist < min_dist) {
                        min_dist = dist;
                        color = s.color;
                    }
                };
            }
            if (min_dist >= 0) {
                image[i * WIDTH + j] = color;
            } else {
                image[i * WIDTH + j] = generate_gradient(j, i, WIDTH, HEIGHT);
            }
        }
    }
    ////RENDERING PART
    std::cout << "Distance to the plane: " << DISTANCE << std::endl;
    std::cout << "Normal vectors nX, nY, nZ:" << std::endl;
    for (int i; i < 3; i++) {
        std::cout << norms[i].to_string() << std::endl;
    }
    //ray casted into the center of the viewing plane should match view vector
//    Vec3d example = vector_for_plane_pixel(WIDTH / 2, HEIGHT / 2, WIDTH, HEIGHT, norms, DISTANCE);
//
//    std::cout << "Sample vector: " << example.to_string() << std::endl;
//    S1.intersect(VIEW_POS, vector_for_plane_pixel(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT, norms, DISTANCE));

    save_image(filename, WIDTH, HEIGHT, image);
    return 0;
}

double get_distance_to_plane(int fov, int plane_width) {
    return plane_width / (2 * tan(fov * M_PI / 360));
}

std::vector<Vec3d> get_norm_vectors(Vec3d v) {
    Vec3d nZ = -v;
    Vec3d nX = Vec3d(1, 0, -v.x / v.z);
    Vec3d nY = Vec3d(0, 1, -v.y / v.z);
    //normalize vectors
    return {nX.normalize(), nY.normalize(), nZ.normalize()};
}

Vec3d vector_for_plane_pixel(int _x, int _y, int width, int height, std::vector<Vec3d> norms, double d) {
    //central pixel of the view plane would have coordinates (0,0)
    //top left - (-width/2, -height/2)
    int x = _x - width / 2;
    int y = -(_y - height / 2);
    //add vectors to each other
    //first go to the center of the plane
    //then shift 'x' normalized vectors left/right
    //then shift 'y' normalized vectors up/down
    Vec3d _v = -norms[2] * d + norms[0] * static_cast<double>(x) + norms[1] * static_cast<double>(y);
    //return normalized vector
    return _v.normalize();
}

RgbColor generate_gradient(const int x, const int y, const int WIDTH, const int HEIGHT) {
    int i = y;
    int j = x;
    return {
            static_cast<char>(round(MAX_CHANNEL * static_cast<double>(i) / HEIGHT)),
            static_cast<char>(round(MAX_CHANNEL * (1 - static_cast<double>(i + j) / (HEIGHT + WIDTH)))),
            static_cast<char>(round(MAX_CHANNEL * static_cast<double>(j) / WIDTH))\
    };
}

void save_image(const char *filename, const int WIDTH, const int HEIGHT, std::vector<RgbColor> image) {
    const int BYTES_PER_PIXEL = 3;
    auto *img_data = (unsigned char *) malloc(WIDTH * HEIGHT * BYTES_PER_PIXEL);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int pixel_array_pos = i * WIDTH + j;
            int byte_array_pos = pixel_array_pos * BYTES_PER_PIXEL;
            RgbColor pixel = image[pixel_array_pos];
            img_data[byte_array_pos] = pixel.r;
            img_data[byte_array_pos + 1] = pixel.g;
            img_data[byte_array_pos + 2] = pixel.b;
        }
    }
    stbi_write_png(filename, WIDTH, HEIGHT, BYTES_PER_PIXEL, img_data, BYTES_PER_PIXEL * WIDTH);
    free(img_data);
}