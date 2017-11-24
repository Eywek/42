/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/24 17:34:32 by valentin         ###   ########.fr       */
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

	nb = ft_get_nb(args, flags);
	size = 0;
	ft_get_number_size((nb < 0 ? -nb : nb), 10, &size);
	if (nb < 0)
		size += 1;
	if (flags.width && flags.zero)
		ft_display_sign(nb, &size, flags);
	if (flags.width > 0 && (width = 0) == 0 && !flags.minus)
		while (width++ < flags.width - size)
			write(STDOUT, (flags.zero) ? "0" : " ", 1);
	if (!flags.width || !flags.zero)
		ft_display_sign(nb, &size, flags);
	ft_putnbr_base_intmax_t((nb < 0 ? -nb : nb), "01234566789", 10);
	if (flags.width > 0 && (width = 0) == 0 && flags.minus)
		while (width++ < flags.width - size)
			write(STDOUT, " ", 1);
	return (flags.width ? flags.width : size);
}

int flag_o(va_list args, t_flags flags)
{
	if (flags.hash_key && flags.precision == -1)
		flags.precision = 0;
	return (ft_pad_nb(args, flags, "01234567", "0"));
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
	return (ft_pad_nb(args, flags, "0123456789", NULL));
}
