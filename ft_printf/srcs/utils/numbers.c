/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:20:18 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 14:37:13 by vtouffet         ###   ########.fr       */
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
		write(STDOUT, "0", 1);
	if (flags->minus && flags->precision != -1)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base));
	width = 0;
	while (width++ < flags->width - (*size + (flags->type == 'p' ? 2 : 0)))
		write(STDOUT, (flags->zero && !flags->minus) ? "0" : " ", 1);
	width = 0;
	while (!flags->minus && width++ < precision)
		write(STDOUT, "0", 1);
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
		write(STDOUT, hash_key_content, ft_strlen(hash_key_content));
	if (flags->hash_key && ((flags->width) && !precision) && flags->type != 'p')
		*size += (int)ft_strlen(hash_key_content);
	return (precision);
}

/*
 ** Display hash_key_content, add some width, handle precision
 ** Return the correct size
*/

int			ft_pad_nb(va_list args, t_flags flags, char *base,
							char *hash_key_content)
{
	int			size;
	uintmax_t	nb;
	int			precision;

	if (flags.precision != 0)
		flags.zero = 0;
	size = 0;
	nb = ft_get_nb_u(args, flags);
	ft_get_number_size_u(nb, ft_strlen(base), &size);
	precision = ft_handle_hash_key(nb, &flags, &size, hash_key_content);
	if (flags.precision == -1 && nb == 0)
		size = 0;
	ft_display_padding(&flags, nb, &size, base);
	if (flags.hash_key && flags.width && !flags.minus && !flags.zero &&
			!precision)
		write(STDOUT, hash_key_content, ft_strlen(hash_key_content));
	if ((!flags.width || !flags.minus) && size > 0)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base));
	if (flags.hash_key && size > 0 && ((!flags.width || flags.minus) ||
			precision) && flags.type != 'p')
		size += (int)ft_strlen(hash_key_content);
	if (size == 0 && flags.type == 'p')
		size = 2;
	return (flags.width - size > 0 ? flags.width : size);
}

/*
 ** Display -, + or space for %d
*/

void		ft_display_sign(intmax_t nb, t_flags flags)
{
	if (nb < 0)
		ft_putchar_fd('-', STDOUT);
	if (flags.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (flags.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
}
