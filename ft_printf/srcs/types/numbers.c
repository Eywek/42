/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 20:52:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "../../includes/core.h"

// TODO: Precision

int	flag_d(va_list args, t_flags flags)
{
	int				size;
	intmax_t		nb;
	int 			width;

	if (flags.length_type == LENGTH_L)
		return (flag_D(args, flags));
	nb = ft_get_nb(args, flags);
	size = 0;
	ft_get_number_size(nb, 10, &size);
	if (flags.width > 0 && (width = 0) == 0)
		while (width++ < flags.width - size)
			write(STDOUT, (flags.zero) ? "0" : " ", 1);
	if (flags.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (flags.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
	ft_putnbr_base_intmax_t(nb, "01234566789", 10);
	return (flags.width ? flags.width : size);
}

int flag_o(va_list args, t_flags flags)
{
	if (flags.length_type == LENGTH_L)
		return (flag_O(args, flags));
	return (ft_pad_nb(args, flags, "01234567", NULL));
}

int flag_x(va_list args, t_flags flags)
{
	return (ft_pad_nb(args, flags, "0123456789abcdef", "0x"));
}

int flag_X(va_list args, t_flags flags)
{
	return (ft_pad_nb(args, flags, "0123456789ABCDEF", "0X"));
}

int flag_u(va_list args, t_flags flags)
{
	if (flags.length_type == LENGTH_L)
		return (flag_U(args, flags));
	return (ft_pad_nb(args, flags, "0123456789", NULL));
}
