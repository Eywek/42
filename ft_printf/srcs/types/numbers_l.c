/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:18:26 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 17:54:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

// TODO
int flag_D(va_list args, t_flags flags)
{
	(void)flags;
	(void)args;
	return (0);
}

int flag_O(va_list args, t_flags flags)
{
	int size;

	(void)flags;
	ft_putnbr_base_unsigned_long(va_arg(args, unsigned long int),
								 "01234567", 8, &size);
	return (size);
}

int flag_U(va_list args, t_flags flags)
{
	(void)flags;
	(void)args;
	return (0);
}
