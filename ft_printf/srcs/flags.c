/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 13:50:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

/*
 ** Set everything to 0
*/

void	ft_init_flags(t_flags *flags)
{
	flags->precision = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->hash_key = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->width = 0;
	flags->length_type = 0;
}

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
	int precision;

	if (**str == '.')
	{
		*str += 1;
		precision = ft_atoi(*str);
		flags->precision = precision;
		while (precision > 0 && (*str = *str + 1))
			precision /= 10;
	}
}

/*
 ** Handle length
*/
void ft_handle_length(char **str, t_flags *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
	{
		*str += 2;
		flags->length_type = LENGTH_HH;
	}
	else if (**str == 'h')
	{
		*str += 1;
		flags->length_type = LENGTH_H;
	}
	else if (**str == 'l' && *(*str + 1) == 'l')
	{
		*str += 2;
		flags->length_type = LENGTH_LL;
	}
	else if (**str == 'l')
	{
		*str += 1;
		flags->length_type = LENGTH_L;
	}
	else if (**str == 'j')
	{
		*str += 1;
		flags->length_type = LENGTH_J;
	}
	else if (**str == 'z')
	{
		*str += 1;
		flags->length_type = LENGTH_Z;
	}
}
