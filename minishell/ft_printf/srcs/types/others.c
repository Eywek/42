/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	type_percentage(va_list args, t_flags *flags)
{
	int		width;

	(void)args;
	if (flags->width)
	{
		if (flags->minus)
			ft_write("%", 1, flags);
		width = 0;
		while (width++ < flags->width - 1)
			ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	}
	if (!flags->width || !flags->minus)
		ft_write("%", 1, flags);
	return ((flags->width) ? flags->width : 1);
}

int	type_n(va_list args, t_flags *flags)
{
	int	*n;

	(void)flags;
	n = va_arg(args, int*);
	*n = flags->total_bytes;
	return (0);
}
