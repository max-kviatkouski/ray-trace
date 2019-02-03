//
// Created by D4PN on 2/2/2019.
//

#include <cstdio>
#include "Vec3d.h"
#include "math.h"
#include "stdlib.h"

Vec3d::Vec3d(double x, double y, double z) : x(x), y(y), z(z) {}

Vec3d Vec3d::operator+(const Vec3d &v) {
    return Vec3d(x + v.x, y + v.y, z + v.z);
}

Vec3d Vec3d::operator-(const Vec3d &v) {
    return Vec3d(x - v.x, y - v.y, z - v.z);
}

Vec3d Vec3d::operator-() {
    return Vec3d(-x, -y, -z);
}

double Vec3d::operator*(const Vec3d &v) {
    return x*v.x + y*v.y + z*v.z;
}

Vec3d Vec3d::operator^(const Vec3d &v) {
    return Vec3d(
            y*v.z - z*v.y,
            z*v.x - x*v.z,
            x*v.y - y*v.x
            );
}

double Vec3d::getLength() {
    return sqrt(x*x + y*y + z*z);
}

Vec3d Vec3d::operator*(const double a) {
    return Vec3d(a*x, a*y, a*z);
}

Vec3d Vec3d::operator/(const double a) {
    return Vec3d(x/a, y/a, z/a);
}

char* Vec3d::to_string() {
    char *output = (char*) malloc(50);
    snprintf(output, 50, "{%f, %f, %f}", x, y, z);
    return output;
}

Vec3d Vec3d::normalize() {
    return *this/this->getLength();
}