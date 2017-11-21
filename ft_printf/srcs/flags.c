/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:34:57 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/
void ft_handle_width(char **str, t_flags *flags)
{
	int width;

	if ((width = ft_atoi(*str)) > 0)
	{
		flags->width = width;
		while (width > 0 && (*str = *str + 1))
			width /= 10;
	}
}
