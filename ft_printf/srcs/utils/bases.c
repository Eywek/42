/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:40:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 16:17:20 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
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

void	ft_putnbr_base_unsigned_long_long(unsigned long long int nbr, char *str,
								 unsigned long long int str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_unsigned_long_long(nbr / str_length, str, str_length,
										  size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_putnbr_base_short_int(short int nbr, char *str,
								 short int str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_short_int(nbr / str_length, str, str_length,
										  size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_putnbr_base_uintmax_t(uintmax_t nbr, char *str,
								uintmax_t str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_uintmax_t(nbr / str_length, str, str_length,
										  size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}


void	ft_putnbr_base_unsigned_char(unsigned char nbr, char *str,
										  unsigned char str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_unsigned_char(nbr / str_length, str, str_length,
										  size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}

void	ft_putnbr_base_size_t(size_t nbr, char *str,
									 size_t str_length, int *size)
{
	*size += 1;
	if (nbr >= str_length)
		ft_putnbr_base_size_t(nbr / str_length, str, str_length,
									 size);
	ft_putchar_fd(str[nbr % str_length], STDOUT);
}
