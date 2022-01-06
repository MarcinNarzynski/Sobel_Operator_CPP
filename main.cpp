#include <iostream>
#include <vector>
#include <algorithm>
#include "bmp_structures.hpp"
#include "file_processor.hpp"

using namespace std;

const string picture_file_name = "oko_17x12.bmp";
const string processed_picture_file_name = "processed_by_sobel.bmp";
const string sobel_file_name = "sobel_tables.conf";

void print_header_data(BMPFileHeader &file_header, BMPInfoHeader &info_header);

int main() {

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    cout << "file header size: " << sizeof(file_header) << endl;
    cout << "info header size: " << sizeof(info_header) << endl;

    read_headers(picture_file_name, file_header, info_header);
    print_header_data(file_header, info_header);

    if (file_header.bfType != 0x4d42) {
        cout << "Invalid BMP file.";
        return 1;
    }

    cout << endl;

    vector3d_u8 picture_data(info_header.biHeight, vector2d_u8(info_header.biWidth, vector1d_u8(info_header.biBitCount / 8)));
    read_pixels_data(picture_file_name, file_header, info_header, picture_data);

    // Bmp file holds lower line as first so lines should be reversed before processing
    reverse(picture_data.begin(), picture_data.end());

    vector3d_8 sobel_tables;
    read_sobel_tables_from_file(sobel_file_name, sobel_tables);

    save_as_bmp_file(processed_picture_file_name, file_header, info_header, picture_data);

    return 0;
}

void print_header_data(BMPFileHeader &file_header,
                       BMPInfoHeader &info_header) {
    cout << "\nFile type: " << file_header.bfType << endl;
    cout << "File size [B]: " << file_header.bfSize << endl;
    cout << "Data offset: " << file_header.bfOffBits << endl;

    cout << "\nPicture width: " << info_header.biWidth << endl;
    cout << "Picture height: " << info_header.biHeight << endl;
    cout << "Color depth [bit]: " << info_header.biBitCount << endl;
    cout << "Compression: " << info_header.biCompression << endl;
    cout << "Image size [B]: " << info_header.biSizeImage << endl;
}
