# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 13:08:42 by vtouffet          #+#    #+#              #
#    Updated: 2017/12/20 18:30:58 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER_NAME=checker
PUSH_SWAP_NAME=push_swap

SRCS_PATH=./srcs/

SRCS_CHECKER_FILES=checker.c checker_error.c display.c operate.c check_order.c
SRCS_CHECKER=$(addprefix $(SRCS_PATH), $(SRCS_CHECKER_FILES))

SRCS_PUSH_SWAP_FILES=push_swap.c checker_error.c display.c operate.c check_order.c
SRCS_PUSH_SWAP=$(addprefix $(SRCS_PATH), $(SRCS_PUSH_SWAP_FILES))

OBJECTS_PATH=./objs/

OBJECTS_CHECKER_FILES=$(SRCS_CHECKER_FILES:.c=.o)
OBJECTS_CHECKER=$(addprefix $(OBJECTS_PATH), $(OBJECTS_CHECKER_FILES))

OBJECTS_PUSH_SWAP_FILES=$(SRCS_PUSH_SWAP_FILES:.c=.o)
OBJECTS_PUSH_SWAP=$(addprefix $(OBJECTS_PATH), $(OBJECTS_PUSH_SWAP_FILES))

COMPILE=gcc -Wall -Wextra -Werror

INCLUDES=-I./includes -I./libft
HEADER=./includes/checker.h

LIB_NAME=libft.a
LIB_PATH=./libft/
LIB=$(LIB_PATH)$(LIB_NAME)

GNL=libs/get_next_line/get_next_line.c

COLOR_RESET=\033[0m
COLOR_PENDING=\033[0;33m
COLOR_SUCCESS=\033[0;32m
COLOR_DEFAULT=\033[1;34m

all: $(CHECKER_NAME) $(PUSH_SWAP_NAME)

$(LIB):
	@echo "$(LIB_NAME)       [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@make -C $(LIB_PATH) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(LIB_NAME)       [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(CHECKER_NAME): $(OBJECTS_CHECKER) $(HEADER) $(LIB)
	@echo "$(CHECKER_NAME)      [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS_CHECKER) $(LIB) $(FT_PRINTF) $(GNL) -o $(CHECKER_NAME) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(CHECKER_NAME)       [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(PUSH_SWAP_NAME): $(OBJECTS_PUSH_SWAP) $(HEADER) $(LIB)
	@echo "$(PUSH_SWAP_NAME)     [$(COLOR_PENDING)Compiling...$(COLOR_RESET)]"
	@$(COMPILE) $(OBJECTS_PUSH_SWAP) $(LIB) $(FT_PRINTF) $(GNL) -o $(PUSH_SWAP_NAME) > /dev/null
	@echo "\033[A\033[K\033[A"
	@echo "$(PUSH_SWAP_NAME)     [$(COLOR_SUCCESS)OK$(COLOR_RESET)]"

$(OBJECTS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir $(OBJECTS_PATH) 2>/dev/null || echo "" > /dev/null
	@$(COMPILE) $(INCLUDES) -c $< -o $@
	@echo "Compiled $@" > /dev/null

clean:
	@make -C $(LIB_PATH) clean > /dev/null
	@rm -rfv $(OBJECTS_PATH) > /dev/null

fclean: clean
	@make -C $(LIB_PATH) fclean > /dev/null
	@rm -rf $(CHECKER_NAME) > /dev/null
	@rm -rf $(PUSH_SWAP_NAME) > /dev/null

re: fclean all

.PHONY: clean fclean re all
