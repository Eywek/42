/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 17:56:59 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/12 00:34:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fillit.h"

/*
 * Generate new map from size and set '.'
*/
char	**ft_new_tab(int size)
{
	int		i;
	char	**map;

	if (!(map = malloc(sizeof(char*) * (size + 1))))
		ft_throw_error();
	i = 0;
	while (i < size)
	{
		if (!(map[i] = ft_strnew(size)))
			ft_throw_error();
		map[i] = ft_memset(map[i], '.', size);
		i++;
	}
	map[i] = 0;
	return (map);
}

/*
 * Remove a tetriminos from the map
*/
void	ft_remove(t_list *tetriminos, char ***map)
{
	int		x;
	int		y;
	char	**ptr;
	
	y = 0;
	ptr = *map;
	while (ptr[y])
	{
		x = 0;
		while (ptr[y][x])
		{
			if (ptr[y][x] == ((t_tetri*)(tetriminos->content))->letter)
				ptr[y][x] = '.';
			x++;
		}
		y++;
	}
}

/*
 * Try to place tetriminos on the map
*/
int		ft_place(t_list *tetri, char ***map, int x, int y, int place)
{
	int		xx;
	int		yy;
	int		block;
	char	**content;
	char	**ptr;

	ptr = *map;
	block = 0;
	yy = -1;
	while ((content = ((t_tetri*)(tetri->content))->minos)[++yy])
	{
		xx = -1;
		while (content[yy][++xx])
		{
			if (!(ptr[y + yy]) )//|| !(ptr[y + yy][x + xx]))
				return (0);
			if (ptr[y + yy][x + xx] == '.' && content[yy][xx] != '.')
			{
				if (place)
					ptr[y + yy][x + xx] = ((t_tetri*)(tetri->content))->letter;
				block++;
			}
		}
	}
	return (block == 4);
}

/*
 * Recursive function, try to solve the map
*/
int		ft_algo(t_list *tetriminos, char ***map)
{
	int		x;
	int		y;
	char	**ptr;

	y = -1;
	ptr = *map;
	while (ptr[++y])
	{
		x = 0;
		while (ptr[y][x])
		{
			if (ptr[y][x] == '.' && ft_place(tetriminos, map, x, y, 0))
			{
				ft_place(tetriminos, map, x, y, 1);
				if (tetriminos->next == NULL)
					return (1);
				if (ft_algo(tetriminos->next, map))
					return (1);
				else
					ft_remove(tetriminos, map);
			}
			++x;
		}
	}
	return (0);
}

/*
 * Solve the map
*/
char	**ft_solve(t_list *tetriminos)
{
	int		map_size;
	char	**map;
	
	map_size = 2;
	map = ft_new_tab(map_size++);
	while (!ft_algo(tetriminos, &map))
	{
		ft_display(map);
		ft_putstr("\n\n");
		// TODO: free the old map
		free(map);
		map = ft_new_tab(map_size++);
	}
	return (map);
}
