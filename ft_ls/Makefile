# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2017/12/07 12:14:15 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

SRCS_PATH=./srcs/
SRCS_FILES=cli.c errors/exceptions.c errors/usage.c utils/directory.c \
			utils/file.c finder.c utils/memory.c utils/debug.c utils/path.c \
			utils/sort.c utils/stats.c display.c utils/compare.c utils/merge.c \
			utils/formatting.c utils/long_display.c utils/display_columns.c \
			utils/window.c
SRCS=$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJECTS_PATH=./objs/
OBJECTS_FILES=$(SRCS_FILES:.c=.o)
OBJECTS=$(addprefix $(OBJECTS_PATH), $(OBJECTS_FILES))

COMPILE=gcc -Wall -Wextra -Werror -O3

INCLUDES=-I./includes -I./libft
HEADER=./includes/ft_ls.h ./includes/prototypes.h ./includes/structs.h

LIB_NAME=libft.a
LIB_PATH=./libft/
LIB=$(LIB_PATH)$(LIB_NAME)

FT_PRINTF_NAME=libftprintf.a
FT_PRINTF_PATH=./libs/ft_printf/
FT_PRINTF=$(FT_PRINTF_PATH)$(FT_PRINTF_NAME)

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	@echo "$(LIB_NAME)       [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C $(LIB_PATH) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(LIB_NAME)       [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "$(FT_PRINTF_NAME) [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C $(FT_PRINTF_PATH) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(FT_PRINTF_NAME) [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "$(NAME)         [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS) $(LIB) $(FT_PRINTF) -o $(NAME) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(NAME)         [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"
	@echo "              [$(COLOR_SUCCESS)FINISHED$(COLOR_RESET)]"

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH)/errors 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH)/utils 2>/dev/null || echo "" > /dev/null
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@
	@echo "Compiled $@" > /dev/null

clean:
	@make -C $(FT_PRINTF_PATH) clean > /dev/null
	@make -C $(LIB_PATH) clean > /dev/null
	@rm -rfv $(OBJECTS_PATH) > /dev/null

fclean: clean
	@make -C $(FT_PRINTF_PATH) fclean > /dev/null
	@make -C $(LIB_PATH) fclean > /dev/null
	@rm -rf $(NAME) > /dev/null

re: fclean all

.PHONY: clean fclean re all
