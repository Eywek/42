/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 20:53:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../includes/core.h"

int	type_c(va_list args, t_flags flags) // TODO: unicode
{
	int c;
	int width;

	if (flags.length_type == LENGTH_L)
		return (type_C(args, flags));
	c = va_arg(args, int);
	width = 0;
	if (flags.width)
	{
		if (flags.minus)
			write(STDOUT, &c, 1);
		while (width++ < flags.width - 1)
			write(STDOUT, (flags.zero && !flags.minus) ? "0" : " ", 1);
	}
	if (!flags.width || !flags.minus)
		write(STDOUT, &c, 1);
	return ((flags.width) ? width : 1);
}

int	type_C(va_list args, t_flags flags) // TODO
{
	wchar_t c;

	(void)flags;
	c = va_arg(args, wchar_t);
	write(STDOUT, &c, 1);
	return (1);
}
