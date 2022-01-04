#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_structures.hpp"

using namespace std;

typedef vector<vector<vector<uint8_t>>> vector3d;
typedef vector<vector<uint8_t>> vector2d;
typedef vector<uint8_t> vector1d;

const string file_name = "oko_20x14.bmp";

void read_headers(const string &file_name, BMPFileHeader &file_header, BMPInfoHeader &info_header);

void print_header_data(BMPFileHeader &file_header, BMPInfoHeader &info_header);

void read_pixels_data(const string &file_name, BMPFileHeader &file_header, BMPInfoHeader &info_header, vector3d &result);

int main() {

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    cout << "file header size: " << sizeof(file_header) << endl;
    cout << "info header size: " << sizeof(info_header) << endl;

    read_headers(file_name, file_header, info_header);
    print_header_data(file_header, info_header);

    if (file_header.bfType != 0x4d42) {
        cout << "Invalid BMP file.";
        return 1;
    }

    cout << endl;

    vector3d picture_data(info_header.biHeight, vector2d(info_header.biWidth, vector1d(info_header.biBitCount / 8)));
    read_pixels_data(file_name, file_header, info_header, picture_data);


    return 0;
}

void read_headers(const string &file_name,
                  BMPFileHeader &file_header,
                  BMPInfoHeader &info_header) {
    ifstream ifs{file_name, ios_base::binary};
    if (ifs.good()) {
        ifs.read((char *) &file_header, sizeof(file_header));
        ifs.read((char *) &info_header, sizeof(info_header));

        ifs.close();
        return;
    }
    cout << "Error in file: " << file_name << endl;
    exit(1);

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

void read_pixels_data(const string &file_name,
                      BMPFileHeader &file_header,
                      BMPInfoHeader &info_header,
                      vector3d &result) {
    int first_pixel_position = file_header.bfOffBits;
    int pict_width = info_header.biWidth;
    int pict_height = info_header.biHeight;
    int bytes_per_color = info_header.biBitCount / 8;

    unsigned int dummy_data_size = (info_header.biSizeImage - pict_width * pict_height * bytes_per_color) / pict_height;

    ifstream ifs{file_name, ios_base::binary};
    if (ifs.good()) {

        // Jump to the pixel data location
        ifs.seekg(first_pixel_position, ifs.beg);

        uint8_t value;
        uint8_t dummy[dummy_data_size];
        for (int hei = 0; hei < pict_height; hei++) {
            for (int wid = 0; wid < pict_width; wid++) {
                for (int color = 0; color < bytes_per_color; color++) {
                    ifs.read((char *) &value, 1);
                    result[hei][wid][color] = value;
                    cout << "Value in result: " << +result[hei][wid][color] << endl;

                }
            }
            // reading dummy bytes after end of each line, dummy_data_size can be zero
            ifs.read((char *) &dummy, dummy_data_size);
        }


        ifs.close();
        return;
    }
    cout << "Error in file during copying picture data: " << file_name << endl;
    exit(1);
}
