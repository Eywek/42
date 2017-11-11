/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:19:43 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/11 11:30:01 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "fillit.h"

/*
 * Generate tab[y][x] for tetriminos from string (buffer)
*/
char		**ft_generate_tetri_tab(char *string, int height, int width)
{
	char	**tab;
	int		y;
	int		x;

	if (!(tab = malloc(sizeof(char*) * height + 1)))
		ft_throw_error();
	y = 0;
	x = 0;
	if (!(tab[y] = malloc(sizeof(char) * (width + 1))))
		ft_throw_error();
	while (*string) // TODO: Ne pas aller trop loin
	{
		if (*string == '\n')
		{
			tab[y++][x] = 0;
			x = 0;
			if (!(tab[y] = malloc(sizeof(char) * (width + 1))))
				ft_throw_error();
		}
		else
			tab[y][x++] = *string;
		string++;
	}
	tab[y] = 0;
	return (tab);
}

t_size		*ft_get_size(char *buffer)
{
	int		i;
	t_size	*size;
	long	pos;
	int		tmp_width;

	if (!(size = malloc(sizeof(t_size))))
		ft_throw_error();
	size->height = 0;
	size->width = 0;
	tmp_width = 0;
	pos = ft_strchr(buffer, '#') - buffer;
	buffer = ft_strsub(buffer, pos, (ft_strrchr(buffer, '#') - buffer + 1) - pos);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			size->height++;
			ft_putnbr(tmp_width);
			ft_putchar('\n');
			size->width = (tmp_width > size->width) ? tmp_width : size->width;
			tmp_width = 0;
		}
		else if (buffer[i] == '#')
			tmp_width++;
		ft_putchar(buffer[i]);
		++i;
	}
	size->width = (tmp_width > size->width) ? tmp_width : size->width;
	ft_putnbr(tmp_width);
	ft_putchar('\n');
	ft_putstr("--\n");
	size->height++;
	return (size);
}

/*
 * Create new element in t_list struct
 * It set width, height, letter (for display) and content in char[y][x]
*/
t_list		*ft_create_tetriminos(char *buffer, char pos)
{
	t_list	*element;
	t_tetri	*tetriminos;
	t_size	*size;
	int		i;

	if (!(tetriminos = malloc(sizeof(t_tetri))))
		ft_throw_error();
	size = ft_get_size(buffer);
	tetriminos->width = size->width;
	tetriminos->height = size->height;
	tetriminos->letter = pos;
	tetriminos->minos = ft_generate_tetri_tab(
			buffer, tetriminos->height, tetriminos->width);
	element = ft_lstnew(tetriminos, sizeof(t_tetri));
	return (element);
}

/*
 * Read in file descriptor, check if tetriminos is valid and create element
 * or throw error if is invalid
*/
t_list		*ft_read_fd(int fd)
{
	t_list	*list;
	int		len;
	char	buf[21];
	char	current_letter;
	int		state;

	list = NULL;
	current_letter = 'A';
	while ((len = read(fd, buf, 21)) >= 20)
	{
		if ((state = ft_bufcheck(buf, len)) == -1)
			ft_throw_error();
		if (list == NULL)
			ft_lstadd(&list, ft_create_tetriminos(buf, current_letter));
		else
			ft_lstaddend(&list, ft_create_tetriminos(buf, current_letter));
	}
	return (list);
}
