# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 10:02:36 by jechoque          #+#    #+#              #
#    Updated: 2017/11/12 16:57:33 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fillit

FLAG=-Wall -Wextra -Werror

HDR=-I ./

SRC=checker.c \
	displayer.c \
	main.c \
	reader.c \
	solver.c \

OBJ=checker.o \
	displayer.o \
	main.o \
	reader.o \
	solver.o \

LIB=./libft/libft.a

$(NAME): ./fillit.h
	make -C ./libft
	gcc $(FLAG) $(SRC) $(HDR) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all
