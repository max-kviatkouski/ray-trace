//
// Created by D4PN on 2/2/2019.
//

#include "Sphere.h"
#include <iostream>
#include <cmath>

Sphere::Sphere(const Vec3d &c, double r, RgbColor color) : c(c), r(r), color(color) {}
Sphere::Sphere() : c(Vec3d(0,0,0)), r(0), color(RgbColor(0,0,0)) {}

bool Sphere::intersect(Vec3d start_point, Vec3d direction, Vec3d &intersection_point) {
#ifdef TRACE_INTERSECT
    std::cout << "Sphere center: " << c.to_string() << " Sphere radius: " << r << std::endl;
    std::cout << "PoV: " << start_point.to_string() << std::endl;
#endif
    //vector from POV to center of the sphere
    Vec3d start_to_center = c - start_point;
#ifdef TRACE_INTERSECT
    std::cout << "Vector to sphere center: " << start_to_center.to_string() << std::endl;
#endif
    if (direction * start_to_center <= 0) {
        //center of the sphere is behind POV
#ifdef TRACE_INTERSECT
        std::cout << "sphere is behind pov" << std::endl;
#endif
        return false;
    } else {
        //calculate projection and then rejection
        //if rejection length is <= sphere radius - we have intersection
        Vec3d projection = direction.normalize() * (start_to_center * direction.normalize());
        Vec3d rejection = -start_to_center + projection;
        Vec3d proj_p = c + rejection;
        float half_chorde = sqrt(r*r - rejection.getLength()*rejection.getLength());
        double distance = (proj_p - start_point).getLength() - half_chorde;
        intersection_point = start_point + direction * distance;
        bool result = rejection.getLength() <= r;
#ifdef TRACE_INTERSECT
        std::cout << "Projection vector: " << projection.to_string() << std::endl;
        std::cout << "Rejection vector: " << rejection.to_string() << "  length: " << rejection.getLength() << std::endl;
        if (result) {
            std::cout << "intersection for pixel" << std::endl;
        } else {
            std::cout << "no intersection" << std::endl;
        }
#endif
        return result;
    }
}