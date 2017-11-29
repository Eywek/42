/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:27:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/29 15:24:53 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/core.h"

int		ft_write_wchar(wint_t c, t_flags flags)
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

void	ft_write_until_percentage(char **format, int *bytes, char **string)
{
	size_t	next;
	t_flags	flags;

	flags.string = string;
	flags.bytes = bytes;
	ft_write(*format, (int)(next = (ft_strchr(*format, '%')) ?
			ft_strchr(*format, '%') - *format : ft_strlen(*format)), flags);
	*format += next;
}

int		ft_write_char(char c, t_flags flags)
{
	return (ft_write(&c, 1, flags));
}

int		ft_write(void *s, int size, t_flags flags)
{
	char	*src;
	char	*str;
	int		previous_size;
	int		i;

	previous_size = *(flags.bytes);
	str = (char *)malloc(sizeof(char) * (previous_size + size + 1));
	if (str == NULL)
		return (-1);
	ft_strcpy(str, *(flags.string));
	i = 0;
	src = s;
	while (i < size)
		str[previous_size++] = src[i++];
	str[previous_size] = '\0';
	free(*(flags.string));
	*(flags.string) = str;
	*(flags.bytes) += size;
	return (size);
}
