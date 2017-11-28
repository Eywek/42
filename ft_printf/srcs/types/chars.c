/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 18:15:57 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../includes/core.h"

int	type_c(va_list args, t_flags flags)
{
	int c;
	int width;

	if (flags.length_type == LENGTH_L)
		return (type_c_upper(args, flags));
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

int	type_c_upper(va_list args, t_flags flags)
{
	wchar_t c;

	(void)flags;
	c = (wchar_t)va_arg(args, wint_t);
	(void)c;
	return (-1);
}
