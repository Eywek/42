cmake_minimum_required(VERSION 3.8)
project(ft_printf)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main_test.c
        srcs/core.c
        libs/libft/ft_strlen.c
        libs/libft/ft_strcmp.c
        libs/libft/ft_strnstr.c
        libs/libft/ft_putchar_fd.c
        libs/libft/ft_putnbr_fd.c
        includes/structs.h
        libs/libft/ft_atoi.c
        libs/libft/ft_isalnum.c
        libs/libft/ft_isdigit.c
        libs/libft/ft_isalpha.c
        libs/libft/ft_islower.c
        libs/libft/ft_isupper.c
        includes/core.h includes/prototypes.h srcs/flags/chars.c srcs/flags/strings.c srcs/flags/numbers.c srcs/flags/others.c)

add_executable(ft_printf ${SOURCE_FILES})
