/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <wchar.h>
#include "../../includes/core.h"

int	type_s(va_list args, t_flags *flags)
{
	char	*s;
	int		width;
	int		size;

	if (flags->length_type == LENGTH_L)
		return (type_s_upper(args, flags));
	s = va_arg(args, char*);
	if (!s)
		size = 6;
	else
		size = (int)ft_strlen(s);
	size = (flags->precision == -1) ? 0 : size;
	if (flags->precision > 0 && flags->precision < size && size > 0)
		size = size - (size - flags->precision);
	if (flags->width)
	{
		if (flags->minus)
			ft_write(s, size, flags);
		width = 0;
		while (width++ < flags->width - size)
			ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	}
	if (!flags->width || !flags->minus)
		ft_write((s) ? s : "(null)", size, flags);
	return (size + (flags->width - size > 0 ? flags->width - size : 0));
}

int	type_s_upper(va_list args, t_flags *flags)
{
	int		size;
	int		width;
	int		tmp;
	wchar_t	*s;

	s = va_arg(args, wchar_t*);
	size = ft_get_wstr_size(s, (flags->precision <= 0) ? 0 : flags->precision);
	if (!s)
		size = 6;
	size = (flags->precision == -1) ? 0 : size;
	if (flags->precision > 0 && flags->precision < size && size > 0)
		size = size - (size - flags->precision);
	if ((width = 0) == 0 && flags->width && !flags->minus)
		while (width++ < flags->width - size)
			ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	if (!s)
		ft_write("(null)", (flags->precision > 0 && flags->precision < 6) ?
						flags->precision : 6, flags);
	tmp = 0;
	while (s && *s && tmp + ft_get_wchar_size(*s) <= size)
		tmp += ft_write_wchar(*s++, flags);
	if (flags->width && flags->minus)
		while (width++ < flags->width - size)
			ft_write(" ", 1, flags);
	return (size + (flags->width - size > 0 ? flags->width - size : 0));
}
