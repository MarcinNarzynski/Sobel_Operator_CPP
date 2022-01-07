
#ifndef PROJ_2_SOBEL_PROCESSOR_HPP
#define PROJ_2_SOBEL_PROCESSOR_HPP

#include "bmp_structures.hpp"

//uint8_t process_pixel(int px, int py, int color, vector3d_8 &sobel_tables, vector3d_u8 &picture_data);

void process_picture(vector3d_8 &sobel_tables, vector3d_u8 &picture_data, vector3d_u8 &result);

#endif //PROJ_2_SOBEL_PROCESSOR_HPP
