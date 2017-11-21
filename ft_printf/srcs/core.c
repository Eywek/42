/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:40:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

/*
 ** List of all types and callbacks
*/

t_types	g_types[ARGS_COUNT] = {
		{"c", flag_c}, {"s", flag_s}, {"d", flag_d}, {"%", flag_percentage},
};

/*
 ** Retrieve and call the function from the name
 ** Use the t_types struct to get callback from name
*/

int	ft_call_function_from_name(char **str, va_list args, t_flags flags)
{
	int i;

	i = 0;
	while (i < ARGS_COUNT)
	{
		if (ft_strnstr(*str, g_types[i].name, ft_strlen(g_types[i].name)))
		{
			*str += ft_strlen(g_types[i].name);
			return (g_types[i].f(args, flags));
		}
		++i;
	}
	return (0);
}

/*
 ** Call all subfonctions to init t_flags struct
 ** Format: %[parameter][flags][width][.precision][length]type
*/

int	ft_handle(char **str, va_list args)
{
	t_flags		flags;
	int 		bytes;

	flags.width = 0;
	flags.space = 0;
	flags.zero = 0;
	flags.hash_key = 0;
	flags.plus = 0;
	flags.minus = 0;
	ft_handle_flags(str, &flags);
	ft_handle_width(str, &flags);
	ft_handle_precision(str, &flags); // TODO
	ft_handle_length(str, &flags); // TODO
	if ((bytes = ft_call_function_from_name(str, args, flags)) > 0)
		return (bytes);
	return (0);
}

/*
 ** First function :
 ** start stdarg,
 ** process format with ft_handle if it's a % or display char
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
		{
			str++;
			bytes += ft_handle(&str, args);
		}
		else
		{
			write(STDOUT, str, 1);
			bytes += 1;
			str++;
		}
	}
	va_end(args);
	return (bytes);
}
