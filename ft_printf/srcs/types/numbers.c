/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:04:33 by vtouffet         ###   ########.fr       */
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

	(void)flags;
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
	if (flags.width_char)
	{
		flags.width_char = (flags.zero) ? '0' : flags.width_char;
		width = 0;
		while (width++ < flags.width - size)
			write(1, &flags.width_char, 1);
	}
	if (flags.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (flags.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
	ft_putnbr_fd(nb, STDOUT);
	return (size);
}
