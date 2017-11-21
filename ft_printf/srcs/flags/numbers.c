/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 13:25:54 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	flag_d(va_list args, t_modifiers modifiers)
{
	int				size;
	int 			nb;
	unsigned int	tmp;

	(void)modifiers;
	nb = va_arg(args, int);
	ft_putnbr_fd(nb, STDOUT);
	size = 0;
	tmp = (nb >= 0) ? nb : -nb;
	while (tmp > 0)
	{
		++size;
		tmp /= 10;
	}
	return (size);
}
