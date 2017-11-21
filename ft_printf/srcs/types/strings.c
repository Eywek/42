/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:46:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_s(va_list args, t_flags flags)
{
	char	*s;
	int		width;
	size_t 	size;

	(void)flags;
	s = va_arg(args, char*);
	size = ft_strlen(s);
	if (flags.width_char)
	{
		width = 0;
		while (width++ < flags.width - (int)size)
			write(1, &flags.width_char, 1);
	}
	write(STDOUT, s, size);
	return ((int)ft_strlen(s));
}
