/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:27:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 15:44:11 by vtouffet         ###   ########.fr       */
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
	int	next;

	if (ft_strchr(*format, '%'))
		next = (int)(ft_strchr(*format, '%') - *format);
	else
		next = (int)ft_strlen(*format);
	next = ft_handle_colors(format, next, flags, next);
	ft_write(*format, next, flags);
	*format += next;
	return (next);
}

int		ft_write_char(char c, t_flags *flags)
{
	return (ft_write(&c, 1, flags));
}

int		ft_write(void *s, int size, t_flags *flags)
{
	int		i;
	char	*str;

	if (flags->bytes + size > BUFF_SIZE)
	{
		write(STDOUT, flags->buffer, (size_t)flags->bytes);
		flags->bytes = 0;
		if (size > BUFF_SIZE)
		{
			write(STDOUT, s, (size_t)size);
			return (size);
		}
	}
	i = 0;
	str = s;
	while (i < size)
		flags->buffer[flags->bytes++] = str[i++];
	flags->total_bytes += size;
	return (size);
}
