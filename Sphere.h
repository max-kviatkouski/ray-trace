//
// Created by D4PN on 2/2/2019.
//

#ifndef RAY_TRACE_SPHERE_H
#define RAY_TRACE_SPHERE_H


#include "Vec3d.h"
#include "RgbColor.h"

class Sphere {
public:
    Vec3d c;
    double r;
    RgbColor color;

    Sphere();
    Sphere(const Vec3d &c, double r, RgbColor color);
    bool intersect(Vec3d start_point, Vec3d direction, Vec3d &intersection_point);
};


#endif //RAY_TRACE_SPHERE_H
