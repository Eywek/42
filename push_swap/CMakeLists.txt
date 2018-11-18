cmake_minimum_required(VERSION 3.8)
project(push_swap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        libs/get_next_line/get_next_line.c
        libft/ft_atoi.c
        libft/ft_push.c
        libft/ft_atoi_base.c
        libft/ft_bzero.c
        libft/ft_dup.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_islower.c
        libft/ft_isprint.c
        libft/ft_isupper.c
        libft/ft_itoa.c
        libft/ft_itoa_base.c
        libft/ft_lstadd.c
        libft/ft_lstaddend.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_max.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_nbrlen.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_reverse_tab.c
        libft/ft_sort_wordtab.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcntfirstchar.c
        libft/ft_strcntlastchar.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strrev.c
        libft/ft_strsplit.c
        libft/ft_strsplitchrset.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_swap.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/ft_get_chartab_size.c
        libft/libft.h
        Makefile libft/ft_getnbr.c libft/ft_free_tab.c libft/ft_in_tab.c srcs/checker_error.c libft/ft_copy_tab.c libft/ft_move_tab.c)

add_executable(push_swap ${SOURCE_FILES} srcs/push_swap.c includes/push_swap.h srcs/display.c srcs/operate.c srcs/check_order.c srcs/numbers.c)
add_executable(checker ${SOURCE_FILES} srcs/checker.c srcs/operate.c includes/checker.h)
