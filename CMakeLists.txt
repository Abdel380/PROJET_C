cmake_minimum_required(VERSION 3.24)
project(photoshop C)

set(CMAKE_C_STANDARD 11)

add_executable(photoshop main.c functions.c functions.h area.c area.h globale.c globale.h pixel.c pixel.h)
