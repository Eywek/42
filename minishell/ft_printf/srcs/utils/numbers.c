/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:20:18 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

/*
 ** Display spaces or zeros if needed
*/

void		ft_display_padding(t_flags *flags, uintmax_t nb, int *size,
								char *base)
{
	int			width;
	int			precision;

	if (flags->precision <= 0 && flags->width <= 0)
	{
		if (flags->type == 'p' && *size > 0)
			*size += 2;
		return ;
	}
	width = 0;
	precision = flags->precision - *size;
	*size = (flags->precision > *size) ? flags->precision : *size;
	while (flags->minus && width++ < precision)
		ft_write("0", 1, flags);
	if (flags->minus && flags->precision != -1)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base), flags);
	width = 0;
	while (width++ < flags->width - (*size + (flags->type == 'p' ? 2 : 0)))
		ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	width = 0;
	while (!flags->minus && width++ < precision)
		ft_write("0", 1, flags);
	if (*size > 0 && flags->type == 'p')
		*size += 2;
}

/*
 ** Display if needed, the hash_key_content
 ** and add the length to the global size
*/

int			ft_handle_hash_key(uintmax_t nb, t_flags *flags, int *size,
							char *hash_key_content)
{
	int precision;

	precision = 0;
	if (nb == 0 && flags->type != 'p')
		flags->hash_key = 0;
	if (flags->hash_key && (!flags->width || flags->minus || flags->zero ||
			(precision = flags->precision > *size)))
		ft_write(hash_key_content, (int)ft_strlen(hash_key_content), flags);
	if (flags->hash_key && ((flags->width) && !precision) && flags->type != 'p')
		*size += (int)ft_strlen(hash_key_content);
	return (precision);
}

/*
 ** Display hash_key_content, add some width, handle precision
 ** Return the correct size
*/

int			ft_pad_nb(va_list args, t_flags *flags, char *base,
							char *hash_key_content)
{
	int			size;
	uintmax_t	nb;
	int			precision;

	if (flags->precision != 0)
		flags->zero = 0;
	size = 0;
	nb = ft_get_nb_u(args, *flags);
	ft_get_number_size_u(nb, ft_strlen(base), &size);
	precision = ft_handle_hash_key(nb, flags, &size, hash_key_content);
	if (flags->precision == -1 && nb == 0)
		size = 0;
	ft_display_padding(flags, nb, &size, base);
	if (flags->hash_key && flags->width && !flags->minus && !flags->zero &&
			!precision)
		ft_write(hash_key_content, (int)ft_strlen(hash_key_content), flags);
	if ((!flags->width || !flags->minus) && size > 0)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base), flags);
	if (flags->hash_key && size > 0 && ((!flags->width || flags->minus) ||
			precision) && flags->type != 'p')
		size += (int)ft_strlen(hash_key_content);
	if (size == 0 && flags->type == 'p')
		size = 2;
	return (flags->width - size > 0 ? flags->width : size);
}

/*
 ** Display -, + or space for %d
*/

void		ft_display_sign(intmax_t nb, t_flags *flags)
{
	if (nb < 0)
		ft_write("-", 1, flags);
	if (flags->plus && nb >= 0)
		ft_write("+", 1, flags);
	else if (flags->space && nb >= 0)
		ft_write(" ", 1, flags);
}

/*
 ** Used into %d to display number / padding / precision
*/

int			ft_display_d(t_flags *flags, int size, int precision, intmax_t nb)
{
	int width_size;
	int width;

	width = 0;
	width_size = 0;
	if (!flags->minus)
	{
		if (flags->width && flags->zero)
			ft_display_sign(nb, flags);
		width_size = ft_pad(flags, size) - size;
	}
	if ((flags->width && (flags->minus || !flags->zero)) || !flags->width)
		ft_display_sign(nb, flags);
	while (width++ < precision)
		ft_write("0", 1, flags);
	if (size > 0)
		ft_putnbr_base_intmax_t_u((uintmax_t)(nb < 0 ? -nb : nb), "0123456789",
								10, flags);
	return (size + width_size);
}
