#include "bmp_calculations.hpp"
#include "bmp_structures.hpp"

int calc_lines_per_iteration(int total_lines,
                             int parts){
    int lines_per_iteration;

    if (total_lines % parts == 0) {
        lines_per_iteration = total_lines / parts;  // total lines perfectly split to x parts
    } else {
        lines_per_iteration = total_lines / parts + 1;  // bigger all parts except last one
    }

    return lines_per_iteration;
}

int calc_dummy_data_size(BMPFileHeader &file_header,
                        BMPInfoHeader &info_header) {
    int pict_width = info_header.biWidth;
    int pict_height = info_header.biHeight;
    int bytes_per_color = info_header.biBitCount / 8;
    int image_size = int(info_header.biSizeImage);

    return (image_size - pict_width * pict_height * bytes_per_color) / pict_height;
}

int calc_bytes_per_line(BMPFileHeader &file_header,
                        BMPInfoHeader &info_header) {
    int pict_width = info_header.biWidth;
    int bytes_per_color = info_header.biBitCount / 8;

    int dummy_data_size = calc_dummy_data_size(file_header, info_header);
    return pict_width * bytes_per_color + dummy_data_size;
}

int calc_first_pixel_position(BMPFileHeader &file_header,
                              BMPInfoHeader &info_header,
                              int part,
                              int lines_per_it){

    int first_pixel_position = int(file_header.bfOffBits);

    int bytes_per_line = calc_bytes_per_line(file_header, info_header);

    return first_pixel_position + part * bytes_per_line * lines_per_it;
}
