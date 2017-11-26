/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/26 16:52:17 by valentin         ###   ########.fr       */
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
	int 			precision;

	nb = ft_get_nb(args, flags);
	size = 0;
	ft_get_number_size_u((uintmax_t)(nb < 0 ? -nb : nb), 10, &size);
	width = 0;
	precision = flags.precision - size;
	size = (flags.precision > size) ? flags.precision : size;
	if (flags.precision == -1 && nb == 0)
		size = 0;
	if (nb >= 0)
		size += (flags.plus) ? 1 : 0 + (flags.space) ? 1 : 0;
	if (nb < 0)
		size += 1;
	if (flags.width && (flags.zero || flags.minus || flags.space))
		ft_display_sign(nb, flags);
	while (flags.minus && width++ < precision)
		write(STDOUT, "0", 1);
	if (flags.minus && size > 0)
		ft_putnbr_base_intmax_t_u((uintmax_t)(nb < 0 ? -nb : nb), "0123456789", 10);
	width = 0;
	while (width++ < flags.width - size)
		write(STDOUT, (flags.zero && !flags.minus && precision <= 0) ? "0" : " ", 1);
	if (!flags.width || (!flags.zero && !flags.minus && !flags.space))
		ft_display_sign(nb, flags);
	width = 0;
	while (!flags.minus && width++ < precision)
		write(STDOUT, "0", 1);
	if ((!flags.width || !flags.minus) && size > 0)
		ft_putnbr_base_intmax_t_u((uintmax_t)(nb < 0 ? -nb : nb), "0123456789", 10);
	return (flags.width > size ? flags.width : size);
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
