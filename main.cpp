#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <math.h>
#include "Vec3d.h"
#include "Sphere.h"
#include <vector>

double get_distance_to_plane(int fov, int plane_width);

//nX, nY, nZ
//nZ is a vector opposite to the view ray by definition
//nX is orthogonal to nZ and parallel to XoZ plane
//nY is orthogonal to nZ and parallel to YoZ plane
//all vectors have length of 1 (pixel) making them basis vectors for the view plane
std::vector<Vec3d> get_norm_vectors(Vec3d v);
//calculate normalized ray vector corresponding to a pixel with coordinates (x, y)
Vec3d vector_for_plane_pixel(int x, int y, int width, int height, std::vector<Vec3d> norms, double d);

int main() {
    //field of view
    const unsigned int FOV = 90;
    Vec3d VIEW_RAY = Vec3d(0.0, 0.0, -1.0);
    Vec3d VIEW_POS = Vec3d(0.0, 0.0, 0.0);
    const int HEIGHT = 600;
    const int WIDTH = 900;

    Sphere S1 = Sphere(Vec3d(0, 0, -600), 100.0, RgbColor(200, 0, 0));

    const char *filename = "test.png";
    const int BYTES_PER_PIXEL = 3;
    const int MAX_CHANNEL = 255;
    unsigned char *img_data = (unsigned char*) malloc(WIDTH * HEIGHT * BYTES_PER_PIXEL);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int ROW_OFFSET = i * WIDTH * BYTES_PER_PIXEL;
            int COLUMN_OFFSET = BYTES_PER_PIXEL * j;
            img_data[ROW_OFFSET + COLUMN_OFFSET] = round(MAX_CHANNEL * static_cast<double>(i) / HEIGHT);
            img_data[ROW_OFFSET + COLUMN_OFFSET + 1] = round(MAX_CHANNEL * (1 - static_cast<double>(i + j) / (HEIGHT + WIDTH)));
            img_data[ROW_OFFSET + COLUMN_OFFSET + 2] = round(MAX_CHANNEL * static_cast<double>(j) / WIDTH);
        }
    }
    double const DISTANCE = get_distance_to_plane(FOV, WIDTH);
    std::cout << "Distance to the plane: " << DISTANCE << std::endl;
    std::cout << "Normal vectors nX, nY, nZ:" << std::endl;
    std::vector<Vec3d> norms = get_norm_vectors(VIEW_RAY);
    for (int i; i < 3; i++) {
        std::cout << "{" << norms[i].x << ", " << norms[i].y << ", " << norms[i].z << "}" << std::endl;
    }
    //ray casted into the center of the viewing plane should match view vector
    Vec3d example = vector_for_plane_pixel(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT, norms, DISTANCE);

    std::cout << "Sample vector: " << example.to_string() << std::endl;

//    S1.intersect(VIEW_POS, vector_for_plane_pixel(WIDTH/2, HEIGHT/2, WIDTH, HEIGHT, norms, DISTANCE));

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Vec3d v = vector_for_plane_pixel(j, i, WIDTH, HEIGHT, norms, DISTANCE);
            if (S1.intersect(VIEW_POS, v)) {
                int ROW_OFFSET = i * WIDTH * BYTES_PER_PIXEL;
                int COLUMN_OFFSET = BYTES_PER_PIXEL * j;
                img_data[ROW_OFFSET + COLUMN_OFFSET] = S1.color.r;
                img_data[ROW_OFFSET + COLUMN_OFFSET + 1] = S1.color.g;
                img_data[ROW_OFFSET + COLUMN_OFFSET + 2] = S1.color.b;
            }
        }
    }
    stbi_write_png(filename, WIDTH, HEIGHT, BYTES_PER_PIXEL, img_data, BYTES_PER_PIXEL*WIDTH);
    free(img_data);
    return 0;
}

double get_distance_to_plane(int fov, int plane_width) {
    return plane_width/(2 * tan(fov * M_PI / 360));
}

std::vector<Vec3d> get_norm_vectors(Vec3d v) {
    Vec3d nZ = -v;
    Vec3d nX = Vec3d(1, 0, -v.x/v.z);
    Vec3d nY = Vec3d(0, 1, -v.y/v.z);
    //normalize vectors
    return {nX.normalize(), nY.normalize(), nZ.normalize()};
}

Vec3d vector_for_plane_pixel(int _x, int _y, int width, int height, std::vector<Vec3d> norms, double d) {
    //central pixel of the view plane would have coordinates (0,0)
    //top left - (-width/2, -height/2)
    int x = _x - width/2;
    int y = -(_y - height/2);
    //add vectors to each other
    //first go to the center of the plane
    //then shift 'x' normalized vectors left/right
    //then shift 'y' normalized vectors up/down
    Vec3d _v = -norms[2]*d + norms[0]*static_cast<double>(x) + norms[1]*static_cast<double>(y);
    //return normalized vector
    return _v.normalize();
}