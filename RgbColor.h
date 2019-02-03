//
// Created by D4PN on 2/2/2019.
//

#ifndef RAY_TRACE_RGBCOLOR_H
#define RAY_TRACE_RGBCOLOR_H


class RgbColor {
public:
    double r,g,b;
    RgbColor();
    RgbColor(double r, double g, double b);
    RgbColor operator*(double intensity);
    void toByteColor(char &r, char &g, char &b);
    char* to_string();
};


#endif //RAY_TRACE_RGBCOLOR_H
