/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 13:53:43 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	ft_putnbr_base_unsigned(unsigned int nbr, char *str,
								unsigned int str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_unsigned(nbr / str_length, str, str_length, size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_putnbr_base_unsigned_long(unsigned long int nbr, char *str,
								unsigned long int str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_unsigned_long(nbr / str_length, str, str_length, size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}
