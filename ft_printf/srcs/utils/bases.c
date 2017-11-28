/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 16:40:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../../includes/core.h"

void	ft_putnbr_base_intmax_t_u(uintmax_t nbr, char *str,
								uintmax_t str_length)
{
	if (nbr >= str_length)
		ft_putnbr_base_intmax_t_u(nbr / str_length, str, str_length);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_get_number_size_u(uintmax_t nbr, uintmax_t str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_get_number_size_u(nbr / str_length, str_length, size);
}
