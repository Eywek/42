/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 11:17:16 by vtouffet         ###   ########.fr       */
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

	if (flags.length_type == LENGHT_L)
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
	char				*nbr;

	if (flags.length_type == LENGHT_L)
		return (flag_O(args, flags));
	nbr = ft_itoa_base(va_arg(args, unsigned int), "01234567");
	write(STDOUT, nbr, ft_strlen(nbr));
	return (0);
}

int flag_x(va_list args, t_flags flags)
{
	char				*nbr;

	(void)flags;
	nbr = ft_itoa_base(va_arg(args, unsigned int), "0123456789abcdef");
	write(STDOUT, nbr, ft_strlen(nbr));
	return (0);
}

int flag_X(va_list args, t_flags flags)
{
	char				*nbr;

	(void)flags;
	nbr = ft_itoa_base(va_arg(args, unsigned int), "01234567ABCDEF");
	write(STDOUT, nbr, ft_strlen(nbr));
	return (0);
}

int flag_u(va_list args, t_flags flags)
{
	char				*nbr;

	if (flags.length_type == LENGHT_L)
		return (flag_U(args, flags));
	ft_putnbr_fd(va_arg(args, unsigned int), STDOUT);
	return (0);
}
