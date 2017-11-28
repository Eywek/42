/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 14:12:42 by vtouffet         ###   ########.fr       */
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
*/

int		ft_handle_flags(char **str, t_flags *flags)
{
	if (*(*str) == '-')
		flags->minus = 1;
	else if (*(*str) == '+')
		flags->plus = 1;
	else if (*(*str) == ' ')
		flags->space = 1;
	else if (*(*str) == '0')
		flags->zero = 1;
	else if (*(*str) == '#')
		flags->hash_key = 1;
	else
		return (0);
	(*str)++;
	return (1);
}

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/

int		ft_handle_width(char **str, t_flags *flags, va_list args)
{
	int width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
				flags->minus = 1;
			flags->width = (width < 0 ? width * -1 : width);
			width = 1;
		}
		else
			flags->width = width;
		while (width > 0 && (*str += 1))
			width /= 10;
		return (1);
	}
	return (0);
}

/*
 ** Handle precision
 ** [.precision]
*/

int		ft_handle_precision(char **str, t_flags *flags, va_list args)
{
	int precision;

	if (**str == '.')
	{
		*str += 1;
		if (!ft_isdigit(**str) && **str != '*')
		{
			flags->precision = -1;
			return (1);
		}
		precision = (**str == '*') ? va_arg(args, int) : ft_atoi(*str);
		flags->precision = (precision == 0 ? -1 : precision);
		if (flags->precision < 0 && flags->precision != -1)
			flags->precision = 0;
		if (**str == '*')
			precision = 1;
		else if (precision == 0)
			*str += 1;
		while (precision > 0 && (*str = *str + 1))
			precision /= 10;
		return (1);
	}
	return (0);
}

/*
 ** Handle length
*/

int		ft_handle_length(char **str, t_flags *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		ft_edit_length_type(str, flags, LENGTH_HH, 2);
	else if (**str == 'h')
		ft_edit_length_type(str, flags, LENGTH_H, 1);
	else if (**str == 'l' && *(*str + 1) == 'l')
		ft_edit_length_type(str, flags, LENGTH_LL, 2);
	else if (**str == 'l')
		ft_edit_length_type(str, flags, LENGTH_L, 1);
	else if (**str == 'j')
		ft_edit_length_type(str, flags, LENGTH_J, 1);
	else if (**str == 'z')
		ft_edit_length_type(str, flags, LENGTH_Z, 1);
	else
		return (0);
	return (1);
}
