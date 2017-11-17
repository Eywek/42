cmake_minimum_required(VERSION 3.8)
project(ft_printf)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main_test.c
        srcs/core.c
        includes/structs.h
        includes/core.h srcs/registerer.c includes/prototypes.h)

add_executable(ft_printf ${SOURCE_FILES})