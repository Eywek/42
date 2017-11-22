/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 14:32:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_c(va_list args, t_flags flags)
{
	int c;
	int width;

	if (flags.length_type == LENGTH_L)
		return (flag_C(args, flags));
	c = va_arg(args, int);
	width = 0;
	if (flags.width)
	{
		if (flags.minus)
			write(STDOUT, &c, 1);
		while (width++ < flags.width - 1)
			write(STDOUT, " ", 1);
	}
	if (!flags.width || !flags.minus)
		write(STDOUT, &c, 1);
	return (1 + width);
}

int	flag_C(va_list args, t_flags flags) // TODO
{
	int c;

	(void)flags;
	c = va_arg(args, int);
	write(STDOUT, &c, 1);
	return (1);
}
