/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 20:18:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "../../includes/core.h"

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
	return (size + (flags.width - size > 0 ? flags.width - size : 0));
}

// TODO: Precision / Width / Flags

int	ft_pad_nb(va_list args, t_flags flags, char *base, char *hash_key_content)
{
	int size;
	int width;

	size = 0;
	intmax_t nb = ft_get_nb(args, flags);
	ft_get_number_size(nb, ft_strlen(base), &size);
	if (nb == 0)
		flags.hash_key = 0;
	if (flags.hash_key && (size += 2) && (!flags.width || flags.minus || flags.zero))
		write(STDOUT, hash_key_content, 2);
	if (flags.width > 0 && (width = 0) == 0)
	{
		if (flags.minus)
			ft_putnbr_base_intmax_t(nb, base, ft_strlen(base));
		while (width++ < flags.width - size)
			write(STDOUT, (flags.zero && !flags.minus) ? "0" : " ", 1);
	}
	if (flags.hash_key && flags.width && !flags.minus && !flags.zero)
		write(STDOUT, hash_key_content, 2);
	if (!flags.width || !flags.minus)
		ft_putnbr_base_intmax_t(nb, base, ft_strlen(base));
	return (flags.width - size > 0 ? flags.width : size);
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
