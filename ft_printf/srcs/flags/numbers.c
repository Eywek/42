/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:57:05 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_d(va_list args, t_modifiers modifiers)
{
	int				size;
	int 			nb;
	unsigned int	tmp;
	int 			width;

	(void)modifiers;
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
	if (modifiers.width_char)
	{
		width = 0;
		while (width++ < modifiers.width - size)
			write(1, &modifiers.width_char, 1);
	}
	if (modifiers.plus && nb >= 0)
		ft_putchar_fd('+', STDOUT);
	else if (modifiers.space && nb >= 0)
		ft_putchar_fd(' ', STDOUT);
	ft_putnbr_fd(nb, STDOUT);
	return (size);
}
