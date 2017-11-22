/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 11:14:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	flag_c(va_list args, t_flags flags)
{
	int c;

	if (flags.length_type == LENGHT_L)
		return (flag_C(args, flags));
	c = va_arg(args, int);
	write(STDOUT, &c, 1);
	return (1);
}

int	flag_C(va_list args, t_flags flags) // TODO
{
	int c;

	(void)flags;
	c = va_arg(args, int);
	write(STDOUT, &c, 1);
	return (1);
}
