#ifndef CALCFRACTALS_H
#define CALCFRACTALS_H

#include "drawBMP.h"
#include "consts.h"
#include <cstdint>
#include <cmath>

const float SCALE_FACTORX = 3.5 / IMAGE_WIDTH;
const float SCALE_FACTORY = 3.0 / IMAGE_HEIGHT;

struct ComplexPoint {
    float r{0.0}; // Real component
    float i{0.0}; // Imaginary component
};

Pixel burningShip(int x, int y, int maxIterations) {
    ComplexPoint c{
        static_cast<float>(x * SCALE_FACTORX) - 2.2f, 
        static_cast<float>(y * SCALE_FACTORY) - 2.0f
    };

    // Use c as the starting point
    ComplexPoint z = c;
    float zr2 = z.r*z.r;
    float zi2 = z.i*z.i;

    int iteration = 0;
    while (zr2 + zi2 <= 4.0f && iteration < maxIterations) {
        float zrn = zr2 - zi2 + c.r;
        float zin = abs(2.0f*z.r*z.i) + c.i;
        
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

    // Otherwise it's not in the set
    float ratio = static_cast<float>(maxIterations-iteration) / maxIterations;
    return Pixel{
        20,
        static_cast<uint8_t>(100*ratio), 
        static_cast<uint8_t>(200*ratio)
    };
}

#endif