/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 20:21:29 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../includes/core.h"

int	type_c(va_list args, t_flags flags)
{
	int	c;
	int	width;

	if (flags.length_type == LENGTH_L)
		return (type_c_upper(args, flags));
	c = va_arg(args, int);
	width = 0;
	if (flags.width)
	{
		if (flags.minus)
			ft_write(&c, 1, flags);
		while (width++ < flags.width - 1)
			ft_write((flags.zero && !flags.minus) ? "0" : " ", 1, flags);
	}
	if (!flags.width || !flags.minus)
		ft_write(&c, 1, flags);
	return ((flags.width) ? width : 1);
}

int	type_c_upper(va_list args, t_flags flags)
{
	(void)flags;
	(void)args;
	return (0);
}
