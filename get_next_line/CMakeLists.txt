cmake_minimum_required(VERSION 3.8)
project(get_next_line)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        get_next_line.c
        get_next_line.h
        main_test.c)

add_executable(get_next_line ${SOURCE_FILES})