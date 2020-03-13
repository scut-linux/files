cmake_minimum_required(VERSION 3.10)
project(FILE C)

set(CMAKE_C_STANDARD 99)

add_executable(FILE lowlevel.c std.c main.c)