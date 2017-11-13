# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2017/11/13 13:54:19 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRCS_PATH=./srcs/
SRCS_FILES=displayer.c reader.c
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJECTS_PATH=./objs/
OBJECTS_FILES=$(SRCS_FILES:.c=.o)
OBJECTS=$(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

COMPILE=gcc -Wall -Werror -Wextra

INCLUDES=-I./includes

LIB_NAME=libft.a
LIB_PATH=./lib/libft/
LIB=$(LIB_PATH)$(LIB_NAME)

all: $(NAME)

$(NAME): $(OBJECTS)
	echoho "Compiling $(LIB_NAME)..."
	make -C $(LIB_PATH)
	echoho "Compiling $(NAME)..."
	$(COMPILE) $(OBJECTS) $(LIB) -o $(NAME)

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir $(OBJECTS_PATH)
	$(COMPILE) $(INCLUDES) -c $< -o $@
	echo "Compiled $@"

clean:
	rm $(OBJECTS)

fclean: clean
	rm $(SRCS)

re: fclean all

.PHONY: clean fclean re all
