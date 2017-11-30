/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:27:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 13:32:12 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/core.h"

int		ft_write_wchar(wint_t c, t_flags *flags)
{
	int size;

	size = 0;
	if (c < 0x007F)
		size += ft_write_char((char)c, flags);
	else if (c < 0x07FF)
	{
		size += ft_write_char((char)((c >> 6) + 0xC0), flags);
		size += ft_write_char((char)((c & 0x3F) + 0x80), flags);
	}
	else if (c < 0xFFFF)
	{
		size += ft_write_char((char)((c >> 12) + 0xE0), flags);
		size += ft_write_char((char)(((c >> 6) & 0x3F) + 0x80), flags);
		size += ft_write_char((char)((c & 0x3F) + 0x80), flags);
	}
	else if (c < 0x10FFFF)
	{
		size += ft_write_char((char)((c >> 18) + 0xF0), flags);
		size += ft_write_char((char)(((c >> 12) & 0x3F) + 0x80), flags);
		size += ft_write_char((char)(((c >> 6) & 0x3F) + 0x80), flags);
		size += ft_write_char((char)((c & 0x3F) + 0x80), flags);
	}
	return (size);
}

int		ft_write_until_percentage(char **format, t_flags *flags)
{
	size_t	next;

	ft_write(*format, (int)(next = (ft_strchr(*format, '%')) ?
			ft_strchr(*format, '%') - *format : ft_strlen(*format)), flags);
	*format += next;
	return ((int)next);
}

int		ft_write_char(char c, t_flags *flags)
{
	return (ft_write(&c, 1, flags));
}

int		ft_write(void *s, int size, t_flags *flags)
{
	(void)flags;
	//printf("-> '%s' = %d\n", s, size);
	write(STDOUT, s, (size_t)size);
	return (size);
//	char	*src;
//	char	*str;
//	int		previous_size;
//	int		i;
//
//	previous_size = flags->bytes;
//	return (size);
}
