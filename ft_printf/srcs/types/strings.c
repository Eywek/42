/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/26 18:32:14 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../includes/core.h"

int	flag_s(va_list args, t_flags flags) // TODO: precision / unicode
{
	char	*s;
	int		width;
	size_t 	size;

	if (flags.length_type == LENGTH_L)
		return (flag_S(args, flags));
	s = va_arg(args, char*);
	if (!s)
		return ((int)write(STDOUT, "(null)", 6));
	size = ft_strlen(s);
	if (flags.precision == -1)
		size = 0;
	if (flags.precision > 0 && flags.precision < size && size > 0)
		size = size - (size - flags.precision);
	if (flags.width)
	{
		if (flags.minus)
			write(STDOUT, s, size);
		width = 0;
		while (width++ < flags.width - (int)size)
			write(STDOUT, (flags.zero && !flags.minus) ? "0" : " ", 1);
	}
	if (!flags.width || !flags.minus)
		write(STDOUT, s, size);
	return ((int)size + (flags.width - (int)size > 0 ? flags.width - (int)size : 0));
}

int	flag_S(va_list args, t_flags flags) // TODO
{
	wint_t	*s;

	s = va_arg(args, wint_t*);
	if (!s)
		return ((int)write(STDOUT, "(null)", 6));
	(void)flags;
	return (0);
}
