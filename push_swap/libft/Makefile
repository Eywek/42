# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/18 16:30:59 by vtouffet          #+#    #+#              #
#    Updated: 2017/12/07 12:25:55 by vtouffet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

SRCS=ft_atoi.c ft_atoi_base.c ft_bzero.c ft_dup.c ft_isalnum.c \
	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islower.c ft_isprint.c \
	ft_isupper.c ft_itoa.c ft_itoa_base.c ft_lstadd.c ft_lstaddend.c \
	ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
	ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
	ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c \
	ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
	ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	ft_strcntfirstchar.c ft_strcntlastchar.c ft_strcpy.c ft_strdel.c \
	ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c \
	ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
	ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strsplitchrset.c ft_strstr.c \
	ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_swap.c \
	ft_sort_wordtab.c ft_reverse_tab.c ft_nbrlen.c ft_max.c ft_getnbr.c \
	ft_free_tab.c ft_in_tab.c ft_copy_tab.c ft_push.c ft_move_tab.c \
	ft_get_chartab_size.c

OBJECTS=$(SRCS:.c=.o)

INCLUDES=./

all: $(NAME)

$(NAME): $(OBJECTS) libft.h
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

%.o: %.c
	@gcc -Wall -Wextra -Werror -I$(INCLUDES) -c $< -o $@

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
