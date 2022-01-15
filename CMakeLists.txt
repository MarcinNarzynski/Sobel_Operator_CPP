cmake_minimum_required(VERSION 3.21)
project(Proj_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Proj_2 main.cpp bmp_structures.hpp file_processor.cpp file_processor.hpp sobel_processor.hpp sobel_processor.cpp bmp_calculations.cpp bmp_calculations.hpp)
