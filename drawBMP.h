#ifndef DRAWBMP_H
#define DRAWBMP_H

#include <cstdint>
#include <vector>

using namespace std;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type{0x4D42};
    uint32_t file_size{0};
    uint16_t reserved1{0};
    uint16_t reserved2{0};
    uint32_t offset_data{54};
};

struct BMPInfoHeader {
    uint32_t info_size{40};
    uint32_t width{0};
    uint32_t height{0};
    uint16_t planes{1};
    uint16_t bits{24}; // 24 bit RGB
    uint32_t compression{0};
    uint32_t image_size{0}; // 0 if compression is 0
    uint32_t x_pixels_per_m{3780};
    uint32_t y_pixels_per_m{3780};
    uint32_t colors_used{0};
    uint32_t important_colors{0};
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue{0};
    uint8_t green{0};
    uint8_t red{0};
};

void drawBMP(string filename, int width, int height, vector<Pixel> pixels) {
    ofstream BMPfin;
    BMPfin.open(filename, ios::binary);

    if(!BMPfin.is_open()) {
        cerr << "File failed to open!" << endl;
        return;
    }

    // Since the num of bytes in each row need to be divisible by 4, 
    // so we go up to the next num divisble by 4 
    int padding = (4 - (width * 3) % 4) % 4;
    int padded_row_size = padding + (width * 3);

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    infoHeader.width = width;
    infoHeader.height = height;
    fileHeader.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + (padded_row_size * height);


    BMPfin.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    BMPfin.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

    uint8_t paddingBytes[3] = {0, 0, 0};
    for(int y = 0; y < height; y++) {
        // Get the index of the first pixel of each row and write the entire row in one go
        int rowIndex = y * width;
        BMPfin.write(reinterpret_cast<const char*>(&pixels[rowIndex]), padded_row_size - padding);
        if(padding > 0) {
            BMPfin.write(reinterpret_cast<const char*>(paddingBytes), padding);
        }
    }

    BMPfin.close();
}

#endif