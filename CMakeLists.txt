cmake_minimum_required(VERSION 3.15)
project(IMS C)

set(CMAKE_C_STANDARD 11)

add_executable(IMS main.c modelib.c modelib.h otherlib.c otherlib.h)