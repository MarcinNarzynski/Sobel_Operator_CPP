#include <iostream>
#include <algorithm>
#include <chrono>

#include "bmp_structures.hpp"
#include "file_processor.hpp"
#include "sobel_processor.hpp"
#include "bmp_calculations.hpp"

using namespace std;

//const string picture_file_name = "oko_17x12.bmp";
string picture_file_name = "owad_800.bmp";
//const string picture_file_name = "morze_2000.bmp";
//const string picture_file_name = "internet_950.bmp";
//const string picture_file_name = "morze_7952x5304.bmp";

string processed_picture_file_name = "processed_by_sobel";
string sobel_file_name = "sobel_tables.conf";
const int min_pictures_lines = 100;
int parts_of_picture = 3;

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

    vector3d_8 sobel_tables;
    read_sobel_tables_from_file(sobel_file_name, sobel_tables);

    int lines_for_processing = info_header.biHeight;
    int lines_per_iteration = calc_lines_per_iteration(lines_for_processing, parts_of_picture);
    if (lines_per_iteration < min_pictures_lines && parts_of_picture > 1) {
        cout << "Picture is to small to split it into " << parts_of_picture << " parts." << endl;
        exit(1);
    }

    cout << "Picture split into " << parts_of_picture << " part(s)." << endl;

    for (int part = 0; part < parts_of_picture; part++) {  // picture split to parts
        cout << "Processing picture part: " << part + 1 << endl;

        int first_pixel_position = calc_first_pixel_position(file_header, info_header, part, lines_per_iteration);

        if (lines_per_iteration > lines_for_processing) {
            lines_per_iteration = lines_for_processing;  // last iteration can process smaller number of lines
        }

        cout << "Lines to process in current iteration: " << lines_per_iteration << endl;
        auto start = chrono::high_resolution_clock::now();

        vector3d_u8 picture_data(lines_per_iteration, vector2d_u8(info_header.biWidth, vector1d_u8(info_header.biBitCount / 8)));
        vector3d_u8 processed_picture_data(picture_data);  // deep copy of picture_data = vector of the same size

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds  >(stop - start);
        cout << "Creating vectors time [ms]: " << duration.count() << endl;

        read_pixels_data(picture_file_name, file_header, info_header, picture_data, first_pixel_position, lines_per_iteration);

        // Bmp file holds lower line as first so lines should be reversed before processing
        reverse(picture_data.begin(), picture_data.end());

        start = chrono::high_resolution_clock::now();
        process_picture(sobel_tables, picture_data, processed_picture_data);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::milliseconds  >(stop - start);
        cout << "Sobel time [ms]: " << duration.count() << endl;

        reverse(processed_picture_data.begin(), processed_picture_data.end());

        string file_for_save = processed_picture_file_name + "_" + to_string(part) + ".bmp";
        save_as_bmp_file(file_for_save, file_header, info_header, processed_picture_data);

        lines_for_processing -= lines_per_iteration;  // reduce number of lines left for processing
    }

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
