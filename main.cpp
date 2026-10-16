#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include "drawBMP.h"
#include "calcFractals.h"

using namespace std;

const int IMAGE_WIDTH = 7000;
const int IMAGE_HEIGHT = 6000;
const int MAX_ITERATIONS = 1000;

int main() {
    vector<Pixel> pixels(IMAGE_WIDTH * IMAGE_HEIGHT);

    for (int y = 0; y < IMAGE_HEIGHT; y++) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            int pixelIndex = y*IMAGE_WIDTH + x;

            // pixels[pixelIndex].red = static_cast<uint8_t>((x*255) / IMAGE_WIDTH);
            // pixels[pixelIndex].green = static_cast<uint8_t>((y*255) / IMAGE_HEIGHT);
            // pixels[pixelIndex].blue = static_cast<uint8_t>(255);

            pixels[pixelIndex] = burningShip(x, y, IMAGE_WIDTH, IMAGE_HEIGHT, MAX_ITERATIONS);
        }
        if((y+1) % 5 == 0) {
            cout << "Row (" << y+1 << "/" << IMAGE_HEIGHT << ") Completed\n";
        }
    }

    drawBMP("output.bmp", IMAGE_WIDTH, IMAGE_HEIGHT, pixels);
    return 0;
}