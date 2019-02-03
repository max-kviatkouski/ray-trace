//
// Created by max on 2/2/19.
//

#ifndef RAY_TRACE_LIGHTSOURCE_H
#define RAY_TRACE_LIGHTSOURCE_H


#include "Vec3d.h"

class LightSource {
public:
    LightSource(const Vec3d &p, double intensity);

public:
    Vec3d p;
    double intensity;
};


#endif //RAY_TRACE_LIGHTSOURCE_H
