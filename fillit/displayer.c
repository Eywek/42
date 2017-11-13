/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:03:07 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/12 16:45:39 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "fillit.h"

/*
 ** Generate new map from size and set '.'
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
 ** Throw an error
*/

void	ft_throw_error(void)
{
	ft_putstr("error\n");
	exit(0);
}

/*
 ** Display the map
*/

void	ft_display(char **map)
{
	if (!map || !*map)
		ft_throw_error();
	while (*map)
	{
		ft_putstr(*(map++));
		ft_putchar('\n');
	}
}
