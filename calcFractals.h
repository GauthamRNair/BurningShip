#ifndef CALCFRACTALS_H
#define CALCFRACTALS_H

#include "drawBMP.h"
#include <cstdint>
#include <cmath>

struct ComplexPoint {
    double r{0.0}; // Real component
    double i{0.0}; // Imaginary component
};

Pixel burningShip(int x, int y, int width, int height, int maxIterations) {
    ComplexPoint c{
        ((x * 3.5) / width) - 2.2, 
        ((y * 3.0) / height) - 2.0
    };

    // Use c as the starting point
    ComplexPoint z = c;

    int iteration = 0;
    while (z.r * z.r + z.i * z.i <= 4 && iteration < maxIterations) {
        ComplexPoint new_z = {
            z.r*z.r - z.i*z.i + c.r,
            fabs(2*z.r*z.i) + c.i
        };
        z = new_z;

        iteration++;
    };

    // Looped long enough that is is likely in the set
    if(iteration == maxIterations) {
        return Pixel{
            0, 0, 0
        };
    }

    // Otherwise it's not in the set
    return Pixel{
        0,
        static_cast<uint8_t>(100*static_cast<double>(maxIterations-iteration) / maxIterations), 
        static_cast<uint8_t>(200*static_cast<double>(maxIterations-iteration) / maxIterations)
    };
}

#endif