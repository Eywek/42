/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 16:09:15 by valentin          #+#    #+#             */
/*   Updated: 2017/11/27 16:12:27 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

/*
 * Add some padding to previous result
*/

int ft_pad(t_flags flags, int size)
{
	int width;

	if (flags.width <= 0)
		return (size);
	width = 0;
	while (width++ < flags.width - size)
		write(STDOUT, (flags.zero && !flags.minus) ? "0" : " ", 1);
	return (size + width - 1);
}
