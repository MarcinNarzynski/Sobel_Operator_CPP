
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "bmp_structures.hpp"

using namespace std;

const char comment_mark = '#';
const char number_separator = ',';

void read_headers(const string &input_file,
                  BMPFileHeader &file_header,
                  BMPInfoHeader &info_header) {
    ifstream ifs{input_file, ios_base::binary};
    if (ifs.good()) {
        ifs.read((char *) &file_header, sizeof(file_header));
        ifs.read((char *) &info_header, sizeof(info_header));

        ifs.close();
        return;
    }
    cout << "Error in file: " << input_file << endl;
    exit(1);

}

void read_pixels_data(const string &input_file,
                      BMPFileHeader &file_header,
                      BMPInfoHeader &info_header,
                      vector3d_u8 &result) {
    int first_pixel_position = file_header.bfOffBits;
    int pict_width = info_header.biWidth;
    int pict_height = info_header.biHeight;
    int bytes_per_color = info_header.biBitCount / 8;

    unsigned int dummy_data_size = (info_header.biSizeImage - pict_width * pict_height * bytes_per_color) / pict_height;

    ifstream ifs{input_file, ios_base::binary};
    if (ifs.good()) {
        cout << "Reading picture data from file..." << endl;
        // Jump to the pixel data location
        ifs.seekg(first_pixel_position, ifstream::beg);

        uint8_t dummy[dummy_data_size];

        for (int hei = 0; hei < pict_height; hei++) {
            for (int wid = 0; wid < pict_width; wid++) {
                for (int color = 0; color < bytes_per_color; color++) {
                    ifs.read((char *) &result[hei][wid][color], 1);
                }
            }
            // reading dummy bytes after end of each line, dummy_data_size can be zero
            ifs.read((char *) &dummy, dummy_data_size);
        }

        ifs.close();
        cout << "...finished reading with success.\n" << endl;

        return;
    }
    cout << "Error in file during copying picture data: " << input_file << endl;
    exit(1);
}

void read_sobel_tables_from_file(const string &input_file,
                                 vector3d_8 &result) {
    cout << "Reading Sobel tables from file..." << endl;
    ifstream ifs{input_file, ios_base::in};

    if (ifs.good()) {
        vector2d_8 table;
        vector1d_8 numbers_in_row;
        string line, text, tmp;
        int tables_count = 0;
        int table_size = 0;

        // read a row and store it in a string variable 'text'
        while (getline(ifs, line)) {
            numbers_in_row.clear();

            // Empty line or beginning from "#"
            if (line.length() == 0 || line[0] == comment_mark) {
                continue;
            }

            // Line with data - 1st value stored as tables count
            if (tables_count == 0) {
                tables_count = stoi(line);
                continue;
            }
            // 2nd value stored as table size
            if (table_size == 0) {
                table_size = stoi(line);
                continue;
            }

            // Now we know number of tables and table size

            // change line to string stream...
            stringstream line_stream(line);

            // ...to split elements to numbers and push them into a vector
            while (getline(line_stream, text, number_separator)) {
                numbers_in_row.push_back(int8_t(stoi(text)));
            }

            // then one line is pushed to table
            table.push_back(numbers_in_row);

            // if table is full of lines - push is to result vector and clear it
            if (table.size() == table_size) {
                result.push_back(table);
                table.clear();
            }

        }  // while

        ifs.close();
        cout << "...finished reading with success.\n" << endl;
        cout << "Total number of Sobel tables: " << tables_count << endl;
        cout << "Size of Sobel table: " << table_size << endl << endl;

        return;
    }
    cout << "Error in file: " << input_file << endl;
    exit(1);
}
