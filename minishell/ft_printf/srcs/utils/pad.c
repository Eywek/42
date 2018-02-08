/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:18:31 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

/*
 ** Add some padding to previous result
*/

int	ft_pad(t_flags *flags, int size)
{
	int width;

	if (flags->width <= 0)
		return (size);
	width = 0;
	while (width++ < flags->width - size)
		ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	return (size + width - 1);
}
