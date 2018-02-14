/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:56:59 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/12 17:44:28 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"

/*
 ** Remove a tetriminos from the map
*/

void	ft_remove(t_list *tetriminos, char ***map)
{
	int		x;
	int		y;
	char	**ptr;
	int		cnt;

	y = 0;
	cnt = 0;
	ptr = *map;
	while (ptr[y])
	{
		x = 0;
		while (ptr[y][x])
		{
			if (cnt == 4)
				return ;
			if (ptr[y][x] == ((t_tetri*)(tetriminos->content))->letter && ++cnt)
				ptr[y][x] = '.';
			x++;
		}
		y++;
	}
}

/*
 ** Try to place tetriminos on the map
*/

#include <unistd.h>
int		ft_place(t_list *tetri, char ***map, int x, int y)
{
	int		xx;
	int		yy;
	int		block;
	char	**content;
	char	**ptr;

	ptr = *map;
	block = 0;
	yy = -1;
	write(1, "-> PLACE ", 9);
	write(1, &(((t_tetri*)(tetri->content))->letter), 1);
	write(1, " AT x=", 6);
	write(1, ft_itoa(x), ft_strlen(ft_itoa(x)));
	write(1, ", y=", 4);
	write(1, ft_itoa(y), ft_strlen(ft_itoa(y)));
	write(1, "\n", 1);
	while ((content = ((t_tetri*)(tetri->content))->minos)[++yy])
	{
		xx = -1;
		while (content[yy][++xx])
		{
			if (!(ptr[y + yy]))
				return (0);
			if (ptr[y + yy][x + xx] == '.' && content[yy][xx] != '.')
			{
				ptr[y + yy][x + xx] = ((t_tetri*)(tetri->content))->letter;
				block++;
			}
		}
	}
	return (block == 4);
}

/*
 ** Check if can place tetriminos on the map
*/

int		ft_check_place(t_list *tetri, char ***map, int x, int y)
{
	int		xx;
	int		yy;
	int		block;
	char	**content;
	char	**ptr;

	ptr = *map;
	block = 0;
	yy = -1;
	write(1, "TEST TO PLACE ", 14);
	write(1, &(((t_tetri*)(tetri->content))->letter), 1);
	write(1, " AT x=", 6);
	write(1, ft_itoa(x), ft_strlen(ft_itoa(x)));
	write(1, ", y=", 4);
	write(1, ft_itoa(y), ft_strlen(ft_itoa(y)));
	write(1, "\n", 1);
	while ((content = ((t_tetri*)(tetri->content))->minos)[++yy])
	{
		xx = -1;
		while (content[yy][++xx])
		{
			if (!(ptr[y + yy]))
				return (0);
			if (ptr[y + yy][x + xx] == '.' && content[yy][xx] != '.')
				block++;
		}
	}
	return (block == 4);
}

/*
 ** Recursive function, try to solve the map
*/

int		ft_algo(t_list *tetriminos, char ***map)
{
	int		x;
	int		y;
	char	**tetris;
	char	**ptr;

	y = -1;
	while ((ptr = *map)[++y])
	{
		x = -1;
		while (ptr[y][++x])
		{
			tetris = ((t_tetri*)(tetriminos->content))->minos;
			if ((ptr[y][x] == '.' || (ptr[y][x] != '.' && tetris[0][0] == '.'))
					&& ft_check_place(tetriminos, map, x, y))
			{
				ft_place(tetriminos, map, x, y);
				ft_display(*map);
				ft_putchar('\n');
				if (tetriminos->next == NULL || ft_algo(tetriminos->next, map))
					return (1);
				else
					ft_remove(tetriminos, map);
			}
		}
	}
	return (0);
}

/*
 ** Solve the map
*/

char	**ft_solve(t_list *tetriminos)
{
	int		map_size;
	char	**map;

	map_size = ft_sqrt(4 * ft_lst_count(tetriminos));
	map_size = 1;
	map = ft_new_tab(map_size++);
	while (!ft_algo(tetriminos, &map))
	{
		free(map);
		map = ft_new_tab(map_size++);
	}
	return (map);
}
