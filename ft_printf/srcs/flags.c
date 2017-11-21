/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:04:57 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/
int ft_flag_width(char *str, t_flags *flags)
{
	int i;

	flags->width_char = 0;
	if (ft_isdigit(*(str + 2)))
	{
		i = 2;
		while (ft_isdigit(*(str + i)))
			flags->width += ft_atoi(str + i++);
		flags->width_char = (*(str + 1));
		return (i - 1);
	}
	else if (ft_isdigit(*(str + 1)))
	{
		flags->width = ft_atoi(str + 1);
		flags->width_char = ' ';
		return (1);
	}
	return (0);
}
