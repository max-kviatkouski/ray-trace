#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "math.h"

int main() {
    //field of view
    const unsigned int FOV = 90;
    const int HEIGHT = 600;
    const int WIDTH = 900;

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
    stbi_write_png(filename, WIDTH, HEIGHT, BYTES_PER_PIXEL, img_data, BYTES_PER_PIXEL*WIDTH);
    std::cout << "Hello, World!" << std::endl;
    free(img_data);
    return 0;
}