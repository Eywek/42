/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/29 12:35:51 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../../includes/core.h"

void	ft_putnbr_base_intmax_t_u(uintmax_t nbr, char *str,
								uintmax_t str_length, t_flags flags)
{
//	if (nbr >= str_length)
//		ft_putnbr_base_intmax_t_u(nbr / str_length, str, str_length, flags);
//	ft_write(&(str[nbr % str_length]), 1, flags);


	char	*res;
	int		size;
	int		i;

	size = 0;
	ft_get_number_size_u(nbr, str_length, &size);
	printf("size = %d\n", size);
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
//	*size += 1;
//	while (nbr >= str_length)
//	{
//		nbr /= str_length;
//		*size += 1;
//	}

//	*size += 1;
//	if (nbr >= str_length)
//		ft_get_number_size_u(nbr / str_length, str_length, size);

//	*size += 1;
//	if (nbr >= str_length)
//		ft_get_number_size_u(nbr / str_length, str_length, size);

//	if (nbr >= 10000000000000000000)
//		return ((void)(*size = 20));
//	else if (nbr >= 1000000000000000000)
//		return ((void)(*size = 19));
//	else if (nbr >= 100000000000000000)
//		return ((void)(*size = 18));
//	else if (nbr >= 10000000000000000)
//		return ((void)(*size = 17));
//	else if (nbr >= 1000000000000000)
//		return ((void)(*size = 16));
//	else if (nbr >= 100000000000000)
//		return ((void)(*size = 15));
//	else if (nbr >= 10000000000000)
//		return ((void)(*size = 14));
//	else if (nbr >= 1000000000000)
//		return ((void)(*size = 13));
//	else if (nbr >= 100000000000)
//		return ((void)(*size = 12));
//	else if (nbr >= 10000000000)
//		return ((void)(*size = 11));
//	else if (nbr >= 1000000000)
//		return ((void)(*size = 10));
//	else if (nbr >= 100000000)
//		return ((void)(*size = 9));
//	else if (nbr >= 10000000)
//		return ((void)(*size = 8));
//	else if (nbr >= 1000000)
//		return ((void)(*size = 7));
//	else if (nbr >= 100000)
//		return ((void)(*size = 6));
//	else if (nbr >= 10000)
//		return ((void)(*size = 5));
//	else if (nbr >= 1000)
//		return ((void)(*size = 4));
//	else if (nbr >= 100)
//		return ((void)(*size = 3));
//	else if (nbr >= 10)
//		return ((void)(*size = 2));
//	return ((void)(*size = 1));
	if (nbr >= str_length * 1000000000000000000)
		return ((void)(*size += 20));
	else if (nbr >= str_length * 100000000000000000)
		return ((void)(*size += 19));
	else if (nbr >= str_length * 10000000000000000)
		return ((void)(*size += 18));
	else if (nbr >= str_length * 1000000000000000)
		return ((void)(*size += 17));
	else if (nbr >= str_length * 100000000000000)
		return ((void)(*size += 16));
	else if (nbr >= str_length * 10000000000000)
		return ((void)(*size += 15));
	else if (nbr >= str_length * 1000000000000)
		return ((void)(*size += 14));
	else if (nbr >= str_length * 100000000000)
		return ((void)(*size += 13));
	else if (nbr >= str_length * 10000000000)
		return ((void)(*size += 12));
	else if (nbr >= str_length * 1000000000)
		return ((void)(*size += 11));
	else if (nbr >= str_length * 100000000)
		return ((void)(*size += 10));
	else if (nbr >= str_length * 10000000)
		return ((void)(*size += 9));
	else if (nbr >= str_length * 1000000)
		return ((void)(*size += 8));
	else if (nbr >= str_length * 100000)
		return ((void)(*size += 7));
	else if (nbr >= str_length * 10000)
		return ((void)(*size += 6));
	else if (nbr >= str_length * 1000)
		return ((void)(*size += 5));
	else if (nbr >= str_length * 100)
		return ((void)(*size += 4));
	else if (nbr >= str_length * 10)
		return ((void)(*size += 3));
	else if (nbr >= str_length)
		return ((void)(*size += 2));
	return ((void)(*size += 1));
}
