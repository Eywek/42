# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2017/11/13 16:10:53 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf

SRCS_PATH=./srcs/
SRCS_FILES=displayer.c reader.c main.c
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJECTS_PATH=./objs/
OBJECTS_FILES=$(SRCS_FILES:.c=.o)
OBJECTS=$(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

COMPILE=gcc -Wall -Werror -Wextra

INCLUDES=-I./includes

LIB_NAME=libft.a
LIB_PATH=./libs/libft/
LIB=$(LIB_PATH)$(LIB_NAME)

GNL=./libs/get_next_line/get_next_line.c

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIB_PATH) > /dev/null
	@echo "$(LIB_NAME) [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS) $(LIB) $(GNL) -o $(NAME) > /dev/null
	@echo "$(NAME)     [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "        [$(COLOR_SUCCESS)FINISHED$(COLOR_RESET)]"

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@
	@echo "Compiled $@" > /dev/null

clean:
	@make -C $(LIB_PATH) clean > /dev/null
	@rm $(OBJECTS)

fclean: clean
	@make -C $(LIB_PATH) fclean > /dev/null
	@rm $(NAME)

re: fclean all

.PHONY: clean fclean re all
