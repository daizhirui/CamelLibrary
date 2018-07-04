cmake_minimum_required(VERSION 3.10)
project(stdio_fp C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-I ./")

add_executable(stdio_fp main.c)
#stdio_fp.c stdio_fp.h soft_fp.c soft_fp.h stdarg.h