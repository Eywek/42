/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:39:35 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Handle flags
 ** Fill t_flags structure and increment the string
**/
void	ft_handle_flags(char **str, t_flags *flags)
{
	if (*(*str) == '-')
	{
		flags->minus = 1;
		(*str)++;
	}
	if (*(*str) == '+')
	{
		flags->plus = 1;
		(*str)++;
	}
	if (*(*str) == ' ')
	{
		flags->space = 1;
		(*str)++;
	}
	if (*(*str) == '0')
	{
		flags->zero = 1;
		(*str)++;
	}
	if (*(*str) == '#')
	{
		flags->hash_key = 1;
		(*str)++;
	}
}

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

/*
 ** Handle precision
 ** [.precision]
*/
void ft_handle_precision(char **str, t_flags *flags)
{
	(void)str;
	(void)flags;
}

/*
 ** Handle length
*/
void ft_handle_length(char **str, t_flags *flags)
{
	(void)str;
	(void)flags;
}
