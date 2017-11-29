/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:28:08 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/29 17:00:57 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	ft_get_wstr_size(wchar_t *s, int max)
{
	int	size;
	int	tmp;

	size = 0;
	while (s && *s)
	{
		if ((tmp = ft_get_wchar_size(*s++)) + size > max && max != 0)
			break ;
		size += tmp;
	}
	return (size);
}

int	ft_get_wchar_size(wint_t c)
{
	if (c < 0x007F)
		return (1);
	else if (c < 0x07FF)
		return (2);
	else if (c < 0xFFFF)
		return (3);
	else if (c < 0x10FFFF)
		return (4);
	return (0);
}
