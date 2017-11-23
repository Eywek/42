/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 18:18:46 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../../includes/core.h"

void	ft_putnbr_base_intmax_t(intmax_t nbr, char *str, intmax_t str_length)
{
	if (nbr >= str_length)
		ft_putnbr_base_intmax_t(nbr / str_length, str, str_length);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_get_number_size(intmax_t nbr, intmax_t str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_get_number_size(nbr / str_length, str_length, size);
}
