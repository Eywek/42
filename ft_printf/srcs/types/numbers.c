/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 15:05:11 by vtouffet         ###   ########.fr       */
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

	// Handle precision
	if (flags.precision != 0)
		flags.zero = 0;

	// Get nb and size
	nb = ft_get_nb(args, flags);
	size = 0;
	ft_get_number_size_u((uintmax_t)(nb < 0 ? -nb : nb), 10, &size);

	// Setup width / precision
	width = 0;
	precision = flags.precision - size;
	size = (flags.precision > size) ? flags.precision : size;

	// Don't display nb if no precision and nb = 0
	if (flags.precision == -1 && nb == 0)
		size = 0;

	// Add to size + or space
	if (nb >= 0)
		size += (flags.plus) ? 1 : 0 + (flags.space) ? 1 : 0;

	// Add to size minus
	if (nb < 0)
		size += 1;

	// Display + / - or space
	if (flags.width && (flags.zero || flags.minus || flags.space))
		ft_display_sign(nb, flags);

	// Display precision
	while (flags.minus && width++ < precision)
		write(STDOUT, "0", 1);

	// Display number if no width or minus
	if (flags.minus && size > 0)
		ft_putnbr_base_intmax_t_u((uintmax_t)(nb < 0 ? -nb : nb), "0123456789", 10);

	// Display width
	width = 0;
	while (width++ < flags.width - size)
		write(STDOUT, (flags.zero && !flags.minus && precision <= 0) ? "0" : " ", 1);

	// Display + / - or space if we have displayed some width
	if (!flags.width || (!flags.zero && !flags.minus && !flags.space))
		ft_display_sign(nb, flags);

	// Display precision
	width = 0;
	while (!flags.minus && width++ < precision)
		write(STDOUT, "0", 1);

	// Display number after width / precision
	if ((!flags.width || !flags.minus) && size > 0)
		ft_putnbr_base_intmax_t_u((uintmax_t)(nb < 0 ? -nb : nb), "0123456789", 10);

	// Return min width or size
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
