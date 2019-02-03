//
// Created by D4PN on 2/2/2019.
//

#ifndef RAY_TRACE_VEC3D_H
#define RAY_TRACE_VEC3D_H


class Vec3d {
public:
    double x, y, z;
    Vec3d(double x, double y, double z);

    Vec3d operator+(const Vec3d &v);
    Vec3d operator-(const Vec3d &v);
    Vec3d operator-();
    Vec3d operator*(const double a);
    Vec3d operator/(const double a);
    double operator*(const Vec3d &v);
    Vec3d operator^(const Vec3d &v);
    double getLength();
    char* to_string();
    Vec3d normalize();
};


#endif //RAY_TRACE_VEC3D_H
