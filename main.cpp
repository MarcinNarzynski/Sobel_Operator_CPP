#include <iostream>
#include <fstream>
#include <vector>
#include "bmp_structures.hpp"

using namespace std;
const string file_name = "oko_15x15.bmp";

void read_headers(const string &file_name, BMPFileHeader &file_header, BMPInfoHeader &info_header);

void print_header_data(BMPFileHeader &file_header, BMPInfoHeader &info_header);

int main() {

    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    vector<uint8_t> raw_data_from_file;

    cout << "file header size: " << sizeof(file_header) << endl;
    cout << "info header size: " << sizeof(info_header) << endl;

    read_headers(file_name, file_header, info_header);
    print_header_data(file_header, info_header);

    if (file_header.bfType != 0x4d42) {
        cout << "Invalid BMP file.";
        return 1;
    }

    unsigned char my_table[info_header.biWidth][info_header.biHeight][3];
    cout << "My Table size: " << sizeof(my_table) << endl;

    unsigned char *p_my_table = NULL;
    p_my_table = my_table[0][0];
    cout << "My Table first elem address: " << my_table << endl;
    cout << "My Table second elem address: " << sizeof(p_my_table) << endl;

    unsigned char value = 0;

    for (int hei=0; hei < info_header.biHeight; hei++) {
        for (int wid=0; wid < info_header.biWidth; wid++) {
            for (int color = 0; color < 3; color++) {
                my_table[hei][wid][color] = value;
                value++;
//                cout << int(*(p_my_table + hei)) << " ";
            }
        }
    }

    cout << endl;




    return 0;
}

void read_headers(const string &file_name, BMPFileHeader &file_header, BMPInfoHeader &info_header) {
    ifstream ifs {file_name, ios_base::binary};
    if (ifs.good())
    {
        ifs.read((char*) &file_header, sizeof(file_header));
        ifs.read((char*) &info_header, sizeof(info_header));

        ifs.close();
        return;
    }
    cout << "Error in file: " << file_name << endl;
    exit(1);

}

void print_header_data(BMPFileHeader &file_header, BMPInfoHeader &info_header) {
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
                      vector<uint8_t> &pixels) {
    int first_pixel_position = file_header.bfOffBits;
    int dummy_data_size = 0;
}
