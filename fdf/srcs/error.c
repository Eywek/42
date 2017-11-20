/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:34:45 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/20 16:43:14 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/fdf.h"

int		ft_is_valid(char *str)
{
	while (*str)
	{
		if (*str != '-' && *str != '+' && !ft_isdigit(*str))
			return (0);
		if ((*str == '-' || *str == '+') && (!*(str + 1) ||
				!ft_isdigit(*(str + 1))))
			return (0);
		++str;
	}
	return (1);
}

void	ft_throw_error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}
