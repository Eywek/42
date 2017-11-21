/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:46:58 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/
int ft_modifier_width(char *str, t_modifiers *modifiers)
{
	int i;

	modifiers->width_char = 0;
	if (ft_isdigit(*(str + 2)))
	{
		i = 2;
		while (ft_isdigit(*(str + i)))
			modifiers->width += ft_atoi(str + i++);
		modifiers->width_char = (*(str + 1));
		return (i - 1);
	}
	else if (ft_isdigit(*(str + 1)))
	{
		modifiers->width = ft_atoi(str + 1);
		modifiers->width_char = ' ';
		return (1);
	}
	return (0);
}
