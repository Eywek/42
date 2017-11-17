# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/12 10:02:36 by jechoque          #+#    #+#              #
#    Updated: 2017/11/17 11:03:53 by vtouffet         ###   ########.fr        #
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

OBJ=$(SRC:.c=.o)

LIB=./libft/libft.a

$(NAME): $(OBJ)
	make -C ./libft
	gcc $(FLAG) $(OBJ) $(HDR) $(LIB) -o $(NAME)

%.o:%.c
	gcc $(FLAG) $(HDR) -c $< -o $@

all: $(NAME)

clean:
	make -C ./libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all
