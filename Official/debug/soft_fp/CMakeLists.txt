cmake_minimum_required(VERSION 3.10)
project(soft_fp C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-DDEBUG -m32")

add_executable(soft_fp soft_fp.c soft_fp.h main.c)