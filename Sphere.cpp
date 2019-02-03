//
// Created by D4PN on 2/2/2019.
//

#include "Sphere.h"
#include <iostream>

Sphere::Sphere(const Vec3d &c, double r, RgbColor color) : c(c), r(r), color(color) {}

bool Sphere::intersect(Vec3d p, Vec3d ray) {
#ifdef TRACE_INTERSECT
    std::cout << "Sphere center: " << c.to_string() << " Sphere radius: " << r << std::endl;
    std::cout << "PoV: " << p.to_string() << std::endl;
#endif
    //vector from POV to center of the sphere
    Vec3d v = c - p;
#ifdef TRACE_INTERSECT
    std::cout << "Vector to sphere center: " << v.to_string() << std::endl;
#endif
    if (ray * v <= 0) {
        //center of the sphere is behind POV
#ifdef TRACE_INTERSECT
        std::cout << "sphere is behind pov" << std::endl;
#endif
        return false;
    } else {
        //calculate projection and then rejection
        //if rejection length is <= sphere radius - we have intersection
        Vec3d proj = ray.normalize() * (v * ray.normalize());
        Vec3d rej = v - proj;
        bool result = rej.getLength() <= r;
#ifdef TRACE_INTERSECT
        std::cout << "Projection vector: " << proj.to_string() << std::endl;
        std::cout << "Rejection vector: " << rej.to_string() << "  length: " << rej.getLength() << std::endl;
        if (result) {
            std::cout << "intersection for pixel" << std::endl;
        } else {
            std::cout << "no intersection" << std::endl;
        }
#endif
        return result;
    }
}