#ifndef CALCFRACTALS_H
#define CALCFRACTALS_H

#include "drawBMP.h"
#include "consts.h"
#include <cstdint>
#include <cmath>
#include <algorithm>

const double SCALE_FACTORX = 3.5 / IMAGE_WIDTH;
const double SCALE_FACTORY = 3.0 / IMAGE_HEIGHT;

struct ComplexPoint {
    double r{0.0}; // Real component
    double i{0.0}; // Imaginary component
};

Pixel burningShip(int x, int y, int maxIterations) {
    ComplexPoint c{
        static_cast<double>(x * SCALE_FACTORX) - 2.2, 
        static_cast<double>(y * SCALE_FACTORY) - 2.0
    };

    // Use c as the starting point
    ComplexPoint z = c;
    double zr2 = z.r*z.r;
    double zi2 = z.i*z.i;

    int iteration = 0;
    while (zr2 + zi2 <= 4.0f && iteration < maxIterations) {
        double zrn = zr2 - zi2 + c.r;
        double zin = abs(2.0f*z.r*z.i) + c.i;
        
        z.r = zrn;
        z.i = zin;

        zr2 = z.r*z.r;
        zi2 = z.i*z.i;
        iteration++;
    };

    // Looped long enough that is is likely in the set
    if(iteration == maxIterations) {
        return Pixel{
            0, 0, 0
        };
    }

    double smoothIteration = iteration + 1.0 - log2(log2(sqrt(zr2*zi2)));

    const float t = smoothIteration * 0.48f;

    // Otherwise it's not in the set
    return Pixel{
        static_cast<uint8_t>(30.0f + 25.0f * std::cos(6.0f * t + 0.0f)),
        static_cast<uint8_t>(100.0f + 55.0f * std::cos(6.0f * t + 0.0f)),
        static_cast<uint8_t>(200.0f + 55.0f * std::cos(6.0f * t + 0.0f))
    };
}

#endif