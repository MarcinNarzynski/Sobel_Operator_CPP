#ifndef PROJ_2_BMP_CALCULATIONS_HPP
#define PROJ_2_BMP_CALCULATIONS_HPP

#include "bmp_structures.hpp"

int calc_lines_per_iteration(int total_lines, int parts);

int calc_dummy_data_size(BMPFileHeader &file_header, BMPInfoHeader &info_header);

int calc_bytes_per_line(BMPFileHeader &file_header, BMPInfoHeader &info_header);

int calc_first_pixel_position(BMPFileHeader &file_header, BMPInfoHeader &info_header, int part, int lines_per_it);


#endif //PROJ_2_BMP_CALCULATIONS_HPP
