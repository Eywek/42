/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 17:05:42 by vtouffet         ###   ########.fr       */
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

int	ft_call_function_from_name(char **str, int add, va_list args,
								  t_flags flags)
{
	int i;

	i = 0;
	while (i < ARGS_COUNT)
	{
		if (ft_strnstr(*str + add + 1, g_types[i].name, ft_strlen(g_types[i].name)))
		{
			*str += add + ft_strlen(g_types[i].name);
			return (g_types[i].f(args, flags));
		}
		++i;
	}
	return (0);
}

/*
 ** Handle flags, set bool into t_flags
 ** Retrieve and call function for each flag found with
 ** ft_call_function_from_name()
 **
 ** **str == the string from the % found to the end of the string
*/

int	ft_handle_types(char **str, va_list args)
{
	int 		bytes;
	t_flags	flags;
	int 		add;

	add = 0;
	/*flags.hash_key = (*(*str + 1) == '#' && (add += 1));
	flags.minus = (*(*str + 1) == '-' && (add += 1));
	flags.zero = (*(*str + 1) == '0' && (add += 1));
	flags.plus = (*(*str + 1) == '+' && (add += 1));
	flags.space = (*(*str + 1) == ' ' && (add += 1));*/
	add += ft_flag_width(*str, &flags);
	if ((bytes = ft_call_function_from_name(str, add, args, flags)) > 0)
		return (bytes);
	return (0);
}

/*
 ** First function :
 ** start stdarg,
 ** process format with ft_handle_types if it's a % or display char
 ** Format: %[parameter][flags][width][.precision][length]type
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
			bytes += ft_handle_types(&str, args);
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
