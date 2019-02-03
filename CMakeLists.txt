cmake_minimum_required(VERSION 3.13)
project(ray_trace)

set(CMAKE_CXX_STANDARD 11)

add_executable(ray_trace main.cpp stb_image.h stb_image_write.h Vec3d.cpp Vec3d.h Sphere.cpp Sphere.h RgbColor.cpp RgbColor.h)