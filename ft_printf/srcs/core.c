/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 13:20:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

t_flags	g_flags[ARGS_COUNT] = {
		{"c", flag_c}, {"s", flag_s}, {"d", flag_d}, {"%", flag_percentage}
};

int	ft_call_function_from_name(char **str, va_list args)
{
	int i;

	i = 0;
	while (i < ARGS_COUNT)
	{
		if (ft_strnstr(*str + 1, g_flags[i].name, ft_strlen(g_flags[i].name)))
		{
			*str += ft_strlen(g_flags[i].name);
			return (g_flags[i].f(args, 0));
		}
		++i;
	}
	return (0);
}

int	ft_handle_percentage(char **str, va_list args)
{
	int bytes;

	if ((bytes = ft_call_function_from_name(str, args)) > 0)
		return (bytes);
	return (0);
}

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
			bytes += ft_handle_percentage(&str, args);
		else
		{
			write(STDOUT, str, 1);
			bytes += 1;
		}
		printf("%d\n");
		str++;
	}
	va_end(args);
	return (bytes);
}
