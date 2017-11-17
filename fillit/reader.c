/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:19:43 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/17 11:01:34 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include "fillit.h"

/*
 ** Remove useless colums
*/

char		**ft_remove_columns(char **tab, int width, int height)
{
	int		i;
	int		y;
	int		pos;
	char	**tmp;

	if (!(tmp = (char**)malloc(sizeof(char*) * (height + 1))))
		ft_throw_error();
	y = 0;
	i = -1;
	pos = 4;
	while (tab[++i])
		pos = (ft_strchr(tab[i], '#') - tab[i] > pos) ? pos :
			ft_strchr(tab[i], '#') - tab[i];
	i = -1;
	while (tab[++i])
		tmp[y++] = ft_strsub(tab[i], pos, width);
	tmp[y] = 0;
	return (tmp);
}

/*
 ** Generate tab[y][x] for tetriminos from string (buffer)
*/

char		**ft_generate_tetri_tab(char *string, int height, int width)
{
	char	**tmp;
	char	**tab;
	int		y;
	int		i;

	if (!(tab = (char**)malloc(sizeof(char*) * (height + 1))))
		ft_throw_error();
	tmp = ft_strsplit(string, '\n');
	y = 0;
	i = -1;
	while (tmp[++i])
	{
		if (ft_strchr(tmp[i], '#'))
		{
			if (!(tab[y] = (char*)malloc(sizeof(char) * 5)))
				ft_throw_error();
			tab[y++] = ft_strdup(tmp[i]);
		}
	}
	tab[y] = 0;
	free(*tmp);
	free(tmp);
	return (ft_remove_columns(tab, width, height));
}

/*
 ** Get width and height from buffer
*/

t_size		*ft_get_size(char *buffer)
{
	int		i;
	t_size	*size;
	int		tmp_width;

	if (!(size = malloc(sizeof(t_size))))
		ft_throw_error();
	size->height = 0;
	size->width = 0;
	tmp_width = 0;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n' && ++size->height &&
			(size->width = (tmp_width > size->width) ? tmp_width : size->width))
			tmp_width = 0;
		else if (buffer[i] == '#')
			tmp_width++;
		if ((buffer[i] == '\n' || buffer[i] == '.') && ((buffer[i + 3] == '#'
			&& (buffer[i + 4] == '#' || buffer[i + 2] == '#')) ||
			(buffer[i + 6] == '#' && (buffer[i + 7] == '#' || buffer[i + 5]))))
			tmp_width++;
	}
	size->width = (tmp_width > size->width) ? tmp_width : size->width;
	return (size->height++ ? size : size);
}

/*
 ** Create new element in t_list struct
 ** It set width, height, letter (for display) and content in char[y][x]
*/

t_list		*ft_create_tetriminos(char *buffer, char letter)
{
	t_list	*element;
	t_tetri	*tetriminos;
	t_size	*size;
	long	pos;

	if (!(tetriminos = (t_tetri*)malloc(sizeof(t_tetri))))
		ft_throw_error();
	pos = ft_strchr(buffer, '#') - buffer;
	size = ft_get_size(ft_strsub(buffer, pos,
				(ft_strrchr(buffer, '#') - buffer + 1) - pos));
	tetriminos->width = size->width;
	tetriminos->height = size->height;
	tetriminos->letter = letter;
	tetriminos->minos = ft_generate_tetri_tab(
			buffer, tetriminos->height, tetriminos->width);
	element = ft_lstnew(tetriminos, sizeof(t_tetri));
	return (element);
}

/*
 ** Read in file descriptor, check if tetriminos is valid and create element
 ** or throw error if is invalid
*/

t_list		*ft_read_fd(int fd)
{
	t_list	*list;
	int		len;
	char	buf[21 + 1];
	char	current_letter;
	int		state;

	list = NULL;
	state = 1;
	current_letter = 'A';
	while ((len = read(fd, buf, 21)))
	{
		buf[len] = '\0';
		if ((state == 1 && (len != 20 && len != 21)) ||
				(state == 0 && len != 20))
			ft_throw_error();
		if ((state = ft_bufcheck(buf, len)) == -1)
			ft_throw_error();
		if (list == NULL)
			ft_lstadd(&list, ft_create_tetriminos(buf, current_letter++));
		else
			ft_lstadd_back(&list, ft_create_tetriminos(buf, current_letter++));
	}
	if (state != 0 || ft_lst_count(list) > 26)
		ft_throw_error();
	return (list);
}
