#include <iostream>
#include <fstream>
#include "bmp_structures.hpp"

using namespace std;
const string file_name = "oko_15x15.bmp";

void read_headers(const string &file_name, BMPFileHeader &file_header, BMPInfoHeader &info_header)
{
    ifstream ifs {file_name, ios_base::binary};
    if (ifs.fail())
    {
        cout << "Error! File doesn't exist: " << file_name << endl;
        exit(1);
    }
    ifs.read((char*) &file_header, sizeof(file_header));
    ifs.read((char*) &info_header, sizeof(info_header));

}

void print_header_data(BMPFileHeader &file_header, BMPInfoHeader &info_header)
{
    cout << "\nFile type: " << file_header.bfType << endl;
    cout << "File size [B]: " << file_header.bfSize << endl;
    cout << "Data offset: " << file_header.bfOffBits << endl;

    cout << "\nPicture width: " << info_header.biWidth << endl;
    cout << "Picture height: " << info_header.biHeight << endl;
    cout << "Color depth [bit]: " << info_header.biBitCount << endl;
    cout << "Compression: " << info_header.biCompression << endl;
    cout << "Image size [B]: " << info_header.biSizeImage << endl;
}

int main() {

    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    cout << "file header size: " << sizeof(file_header) << endl;
    cout << "info header size: " << sizeof(info_header) << endl;

    read_headers(file_name, file_header, info_header);
    print_header_data(file_header, info_header);

    return 0;
}
