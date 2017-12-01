# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2017/12/01 11:18:37 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a

SRCS_PATH=./srcs/
SRCS_FILES=core.c flags.c types/chars.c types/numbers.c types/others.c \
			types/pointers.c types/strings.c types/numbers_l.c utils/bases.c \
			utils/numbers.c types/arrays.c utils/pad.c utils/flags.c \
			utils/get_numbers.c utils/write.c utils/wchars.c types/floats.c \
			utils/floats.c utils/colors.c types/binary.c
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_FILES))

LIB_SRCS_PATH=./libs/libft/
LIB_SRCS_FILES=ft_strcmp.c ft_strlen.c ft_strnstr.c ft_putnbr_fd.c \
				ft_putchar_fd.c ft_atoi.c ft_isalnum.c ft_isdigit.c \
				ft_isalpha.c ft_islower.c ft_isupper.c ft_itoa_base.c \
				ft_strchr.c ft_isprint.c ft_strnew.c ft_memalloc.c ft_bzero.c \
				ft_strcat.c ft_strsub.c ft_strncpy.c ft_strjoin.c ft_strcpy.c \
				ft_strnstr.c

LIB_SRCS=$(addprefix $(LIB_SRCS_PATH), $(LIB_SRCS_FILES))

LIB_OBJECTS_PATH=./objs/
LIB_OBJECTS_FILES=$(LIB_SRCS_FILES:.c=.o)
LIB_OBJECTS=$(addprefix $(LIB_OBJECTS_PATH), $(LIB_OBJECTS_FILES))

OBJECTS_PATH=./objs/
OBJECTS_FILES=$(SRCS_FILES:.c=.o)
OBJECTS=$(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

COMPILE=gcc -Wall -Wextra -Werror

INCLUDES=-I./includes -I./libs/libft
HEADERS_PATH=./includes/
HEADERS_FILES=core.h prototypes.h structs.h
HEADERS=$(addprefix $(HEADERS_PATH), $(HEADERS_FILES))

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(NAME)

$(NAME): $(OBJECTS) $(LIB_OBJECTS) $(HEADERS)
	@echo "$(NAME)     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@ar rc $(NAME) $(OBJECTS) $(LIB_OBJECTS) $(LIB)
	@ranlib $(NAME)
	@echo "\033[A\033[K\033[A"
	@echo "$(NAME)     [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "                  [$(COLOR_SUCCESS)FINISHED$(COLOR_RESET)]"

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)types 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)utils 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@

$(LIB_OBJECTS_PATH)%.o: $(LIB_SRCS_PATH)%.c
	@mkdir $(LIB_OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@

clean:
	@rm -fv $(OBJECTS) > /dev/null
	@rm -rf $(OBJECTS_PATH) > /dev/null

fclean: clean
	@rm -fv $(NAME) > /dev/null

re: fclean all

.PHONY: clean fclean re all
