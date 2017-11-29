/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/29 12:53:55 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../../includes/core.h"

void	ft_putnbr_base_intmax_t_u(uintmax_t nbr, char *str,
								uintmax_t str_length, t_flags flags)
{
	char	*res;
	int		size;
	int		i;

	size = 0;
	ft_get_number_size_u(nbr, str_length, &size);
	if (!(res = malloc(sizeof(char) * size)))
		return ;
	i = size;
	while (i > 0)
	{
		res[--i] = str[nbr % str_length];
		nbr /= str_length;
	}
	ft_write(res, size, flags);
	free(res);
}

void	ft_get_number_size_u(uintmax_t nbr, uintmax_t str_length, int *size)
{
	*size += 1;
	while (nbr >= str_length)
	{
		nbr /= str_length;
		*size += 1;
	}
}
