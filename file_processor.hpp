
#ifndef PROJ_2_FILE_PROCESSOR_HPP
#define PROJ_2_FILE_PROCESSOR_HPP

#include <string>
#include "bmp_structures.hpp"

void read_headers(const string &input_file, BMPFileHeader &file_header, BMPInfoHeader &info_header);

void read_pixels_data(const string &input_file, BMPFileHeader &file_header, BMPInfoHeader &info_header, vector3d_u8 &result);

void read_sobel_tables_from_file(const string &input_file, vector3d_8 &result);

#endif //PROJ_2_FILE_PROCESSOR_HPP
