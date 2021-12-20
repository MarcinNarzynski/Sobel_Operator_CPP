
#include <cstdint>

#pragma pack(push, 1)

struct BMPFileHeader {
    uint16_t bfType{0x4D42};            // File type always BM which is 0x4D42
    uint32_t bfSize{0};                 // Size of the file (in bytes)
    uint16_t bfReserved1{0};            // Reserved, always 0
    uint16_t bfReserved2{0};            // Reserved, always 0
    uint32_t bfOffBits{0};              // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
    uint32_t biSize{0};                 // Size of this header (in bytes)
    int32_t biWidth{0};                 // width of bitmap in pixels
    int32_t biHeight{0};                // width of bitmap in pixels
    //       (if positive, bottom-up, with origin in lower left corner)
    //       (if negative, top-down, with origin in upper left corner)
    uint16_t biPlanes{1};               // No. of planes for the target device, this is always 1
    uint16_t biBitCount{0};             // No. of bits per pixel
    uint32_t biCompression{0};          // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t biSizeImage{0};            // 0 - for uncompressed images
    uint32_t biXpixelsPerMeter{0};
    uint32_t biYpixelsPerMeter{0};
    uint32_t biColorsUsed{0};           // No. color indexes in the color table. Use 0 for the max number of colors allowed by biBitCount
    uint32_t biColorsImportant{0};      // No. of colors used for displaying the bitmap. If 0 all colors are required
};

#pragma pack(pop)
