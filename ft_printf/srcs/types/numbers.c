/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 13:55:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_d(va_list args, t_flags flags)
{
	int				size;
	int 			nb;
	unsigned int	tmp;
	int 			width;

	if (flags.length_type == LENGTH_L)
		return (flag_D(args, flags));
	nb = va_arg(args, int);
	size = 0;
	tmp = (unsigned int)((nb >= 0) ? nb : -nb);
	while (tmp > 0)
	{
		++size;
		tmp /= 10;
	}
	if (nb < 0)
		++size;
	if (flags.width > 0)
	{
		width = 0;
		while (width++ < flags.width - size)
			write(STDOUT, (flags.zero) ? "0" : " ", 1);
	}
	if (flags.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (flags.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
	ft_putnbr_fd(nb, STDOUT);
	return (size + (flags.width - size > 0 ? flags.width - size : 0));
}

// TODO: Precision / Width / Flags

int flag_o(va_list args, t_flags flags)
{
	int size;

	if (flags.length_type == LENGTH_L)
		return (flag_O(args, flags));
	ft_putnbr_base_unsigned(va_arg(args, unsigned int), "01234567", 8, &size);
	return (size);
}

int flag_x(va_list args, t_flags flags)
{
	int size;

	if (flags.hash_key)
		write(STDOUT, "0x", 2);
	if (flags.length_type == LENGTH_L)
		ft_putnbr_base_unsigned_long(va_arg(args, unsigned long int),
									 "0123456789abcdef", 16, &size);
	else
		ft_putnbr_base_unsigned(va_arg(args, unsigned int), "0123456789abcdef",
								16, &size);
	return (size);
}

int flag_X(va_list args, t_flags flags)
{
	int size;

	if (flags.hash_key)
		write(STDOUT, "0X", 2);
	if (flags.length_type == LENGTH_L)
		ft_putnbr_base_unsigned_long(va_arg(args, unsigned long int),
									 "0123456789ABCDEF", 16, &size);
	else
		ft_putnbr_base_unsigned(va_arg(args, unsigned int), "0123456789ABCDEF",
								16, &size);
	return (size);
}

int flag_u(va_list args, t_flags flags)
{
	char				*nbr;

	if (flags.length_type == LENGTH_L)
		return (flag_U(args, flags));
	ft_putnbr_fd_unsigned(va_arg(args, unsigned int), STDOUT);
	return (0);
}
