/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 14:03:07 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/10 15:28:31 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "fillit.h"

void	ft_throw_error()
{
	ft_putstr("error\n");
	exit(0);
}

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
