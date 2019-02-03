//
// Created by D4PN on 2/2/2019.
//

#include <cmath>
#include "RgbColor.h"
#include <algorithm>
#include <cstdio>

RgbColor::RgbColor(double r, double g, double b) : r(r), g(g), b(b) {}

RgbColor::RgbColor() : r(0), g(0), b(0) {}

RgbColor RgbColor::operator*(double intensity) {
    return {
            intensity * r,
            intensity * g,
            intensity * b
    };
}

void RgbColor::toByteColor(char &_r, char &_g, char &_b) {
    double max = std::max(r, std::max(g, b));
    RgbColor c = RgbColor(*this);
    if (max > 1.0) {
        c = c * (1.0/max);
    }
    _r = (char)(255 * std::max(0., std::min(1., c.r)));
    _g = (char)(255 * std::max(0., std::min(1., c.g)));
    _b = (char)(255 * std::max(0., std::min(1., c.b)));
}

char *RgbColor::to_string() {
    auto *output = (char*) malloc(50);
    snprintf(output, 50, "(%f, %f, %f)", r, g, b);
    return output;
}
