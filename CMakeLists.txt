cmake_minimum_required(VERSION 3.12)
project(IMS C)

set(CMAKE_C_STANDARD 11)

add_executable(IMS main.c modelib.c modelib.h otherlib.c otherlib.h loglib.h loglib.c)