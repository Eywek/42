/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:26:05 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

/*
 ** List of all flags and callbacks
*/

t_flags	g_flags[ARGS_COUNT] = {
		{"c", flag_c}, {"s", flag_s}, {"d", flag_d}, {"%", flag_percentage},
};

/*
 ** Retrieve and call the function from the name
 ** Use the t_flags struct to get callback from name
*/

int	ft_call_function_from_name(char **str, int add, va_list args,
								  t_modifiers modifiers)
{
	int i;

	i = 0;
	while (i < ARGS_COUNT)
	{
		if (ft_strnstr(*str + add + 1, g_flags[i].name, ft_strlen(g_flags[i].name)))
		{
			*str += add + ft_strlen(g_flags[i].name);
			return (g_flags[i].f(args, modifiers));
		}
		++i;
	}
	return (0);
}

/*
 ** Handle width
 ** (eg. %3d ->   1 || %03d -> 001)
*/
int ft_modifier_width(char *str, t_modifiers *modifiers)
{
	if (ft_isalnum(*(str + 1))) // width
	{
		if (ft_isdigit(*(str + 2)))
		{
			modifiers->width = ft_atoi(str + 2);
			modifiers->width_char = (*(str + 1));
			return (2);
		}
		else if (ft_isdigit(*str + 1))
		{
			modifiers->width = ft_atoi(str + 1);
			modifiers->width_char = ' ';
			return (1);
		}
	}
	return (0);
}

/*
 ** Handle modifiers, set bool into t_modifiers
 ** Retrieve and call function for each flag found with
 ** ft_call_function_from_name()
 **
 ** **str == the string from the % found to the end of the string
*/

int	ft_handle_flags(char **str, va_list args)
{
	int 		bytes;
	t_modifiers	modifiers;
	int 		add;

	add = 0;
	modifiers.hash_key = 0;
	modifiers.minus = 0;
	modifiers.plus = 0;
	modifiers.space = 0;
	modifiers.zero = 0;
	modifiers.width_char = 0;
	add += ft_modifier_width(*str, &modifiers);
	if ((bytes = ft_call_function_from_name(str, add, args, modifiers)) > 0)
		return (bytes);
	return (0);
}

/*
 ** First function :
 ** start stdarg,
 ** process format with ft_handle_flags if it's a % or display char
*/

int	ft_printf(const char *restrict format, ...)
{
	char	*str;
	int		bytes;
	va_list args;

	bytes = 0;
	va_start(args, format);
	str = (char*)format;
	while (*str)
	{
		if (*str == '%')
			bytes += ft_handle_flags(&str, args);
		else
		{
			write(STDOUT, str, 1);
			bytes += 1;
		}
		str++;
	}
	va_end(args);
	return (bytes);
}
