/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:45:58 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_s(va_list args, t_modifiers modifiers)
{
	char	*s;
	int		width;
	size_t 	size;

	(void)modifiers;
	s = va_arg(args, char*);
	size = ft_strlen(s);
	if (modifiers.width_char)
	{
		width = 0;
		while (width++ < modifiers.width - (int)size)
			write(1, &modifiers.width_char, 1);
	}
	write(STDOUT, s, size);
	return ((int)ft_strlen(s));
}
