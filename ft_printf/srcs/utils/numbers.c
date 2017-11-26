/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:20:18 by valentin          #+#    #+#             */
/*   Updated: 2017/11/26 16:37:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

intmax_t	ft_get_nb(va_list args, t_flags flags)
{
	intmax_t	nbr;

	nbr = va_arg(args, intmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (intmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

uintmax_t	ft_get_nb_u(va_list args, t_flags flags)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (unsigned char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (unsigned short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (unsigned long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (unsigned long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (uintmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

/*
 ** Display spaces or zeros if needed
 **
*/

void		ft_display_padding(t_flags *flags, uintmax_t nb, int *size,
							   char *base)
{
	int			width;
	int 		precision;

	if (flags->precision <= 0 && flags->width <= 0)
		return ;
	width = 0;
	precision = flags->precision - *size;
	*size = (flags->precision > *size) ? flags->precision : *size;
	while (flags->minus && width++ < precision)
		write(STDOUT, "0", 1);
	if (flags->minus && flags->precision != -1)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base));
	width = 0;
	while (width++ < flags->width - *size)
		write(STDOUT, (flags->zero && !flags->minus) ? "0" : " ", 1);
	width = 0;
	while (!flags->minus && width++ < precision)
		write(STDOUT, "0", 1);
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

	size = 0;
	nb = ft_get_nb_u(args, flags);
	ft_get_number_size_u(nb, ft_strlen(base), &size);
	if (nb == 0)
		flags.hash_key = 0;
	if (flags.hash_key && (size += ft_strlen(hash_key_content)) &&
			(!flags.width || flags.minus || flags.zero))
		write(STDOUT, hash_key_content, ft_strlen(hash_key_content));
	if (flags.precision == -1  && nb == 0)
		size = 0;
	ft_display_padding(&flags, nb, &size, base);
	if (flags.hash_key && flags.width && !flags.minus && !flags.zero)
		write(STDOUT, hash_key_content, ft_strlen(hash_key_content));
	if ((!flags.width || !flags.minus) && size > 0)
		ft_putnbr_base_intmax_t_u(nb, base, ft_strlen(base));
	return (flags.width - size > 0 ? flags.width : size);
}

/*
 ** Display -, + or space for %d
*/

void ft_display_sign(intmax_t nb, t_flags flags)
{
	if (nb < 0)
		ft_putchar_fd('-', STDOUT);
	if (flags.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (flags.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
}
