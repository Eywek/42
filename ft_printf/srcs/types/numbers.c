/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 14:54:59 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>
#include "../../includes/core.h"

int	type_d(va_list args, t_flags flags)
{
	int				size;
	intmax_t		nb;
	int				width;
	int				precision;

	if (flags.precision != 0)
		flags.zero = 0;
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

int	type_o(va_list args, t_flags flags)
{
	int			size;
	int			nb_size;
	uintmax_t	nb;

	if (flags.precision != 0)
		flags.zero = 0;
	size = 0;
	nb = ft_get_nb_u(args, flags);
	if (flags.precision >= 0 || nb > 0)
		ft_get_number_size_u(nb, 8, &size);
	if (flags.hash_key && (nb > 0 || flags.precision < 0))
		size += 1;
	nb_size = size;
	size = (flags.precision > size) ? flags.precision : size;
	if (flags.width && !flags.minus)
		size = ft_pad(flags, size);
	if (flags.hash_key && (nb > 0 || flags.precision < 0))
		write(STDOUT, "0", 1);
	while (nb_size++ < flags.precision)
		write(STDOUT, "0", 1);
	if (flags.precision >= 0 || nb > 0)
		ft_putnbr_base_intmax_t_u(nb, "01234567", 8);
	if (flags.width && flags.minus)
		size = ft_pad(flags, size);
	return (size);
}

int	type_x(va_list args, t_flags flags)
{
	return (ft_pad_nb(args, flags, "0123456789abcdef", "0x"));
}

int	type_x_upper(va_list args, t_flags flags)
{
	return (ft_pad_nb(args, flags, "0123456789ABCDEF", "0X"));
}

int	type_u(va_list args, t_flags flags)
{
	return (ft_pad_nb(args, flags, "0123456789", NULL));
}
