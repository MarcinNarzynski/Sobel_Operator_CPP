
#include <cmath>
#include <iostream>

#include "bmp_structures.hpp"

using namespace std;

const uint8_t background_color = 222;

uint8_t average(vector<int> &numbers) {
    float sum = 0;
    for (auto it: numbers) {
        sum += float(it);
    }
    return uint8_t(lround(sum / float(numbers.size())));
}

uint8_t process_pixel(int px, int py, int color, vector3d_8 &sobel_tables, vector3d_u8 &picture_data) {

    vector<int> pixel_processed_by_all_tables;  // this values may be bigger than 255 and lower then 0

    for (const vector2d_8 &s_tab: sobel_tables ) {  // iterate through Sobel tables
        int s_tab_size = int(s_tab.size());
        int mid_idx = s_tab_size / 2;
        int pixel_value_sum = 0;

        int pict_hei = int(picture_data.size());
        int pict_wid = int(picture_data[0].size());

        if ((py - mid_idx < 0) || (py + mid_idx >= pict_hei) ||
            (px - mid_idx < 0) || (px + mid_idx >= pict_wid)) {

            return background_color;  // return if processed pixel is on border of picture
        }

        for (int row = 0; row < s_tab_size; row++) {        // iterate through Sobel table rows...
            for (int col = 0; col < s_tab_size; col++) {    // ...and columns

                int8_t s_value = s_tab[row][col];

                int pixel_ind_x = px - mid_idx + col;
                int pixel_ind_y = py - mid_idx + row;

                int pixel_value = picture_data[pixel_ind_y][pixel_ind_x][color];

                pixel_value_sum += pixel_value * s_value;
            }
        }
        pixel_processed_by_all_tables.push_back(abs(pixel_value_sum));  // manual says no word about module here!
    }
    return average(pixel_processed_by_all_tables);
}

void process_picture(vector3d_8 &sobel_tables, vector3d_u8 &picture_data, vector3d_u8 &result) {

    cout << "Sobel processing has started..." << endl;
    int pict_hei = int(picture_data.size());
    int pict_wid = int(picture_data[0].size());
    int color_chan = int(picture_data[0][0].size());

    for (int color = 0; color < color_chan; color++) {
        for (int row = 0; row < pict_hei; row++) {
            if ((pict_hei - row) % 100 == 0) {
                cout << "  Color left: " << color_chan - color
                     << "   picture lines left: " << pict_hei - row << "  \r" << flush;
            }
            for (int col = 0; col < pict_wid; col++) {
                uint8_t pixel_value = process_pixel(col, row, color, sobel_tables, picture_data);
                result[row][col][color]=pixel_value;
            }
        }
    }
    cout << "...Sobel processing finished with success.                   \n" << endl;
}

