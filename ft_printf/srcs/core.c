/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/20 19:09:46 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

int	c(va_list args, int flag)
{
	int c;

	(void)flag;
	c = va_arg(args, int);
	write(STDOUT, &c, 1);
	return (1);
}

int	s(va_list args, int flag)
{
	char *s;

	(void)flag;
	s = va_arg(args, char*);
	write(STDOUT, s, ft_strlen(s));
	return ((int)ft_strlen(s));
}

int	d(va_list args, int flag)
{
	int size;
	int nb;

	(void)flag;
	nb = va_arg(args, int);
	ft_putnbr_fd(nb, STDOUT);
	size = 1;
	while (nb /= 10 > 0)
		++size;
	return (size);
}

int	percentage(va_list args, int flag)
{
	(void)flag;
	(void)args;
	write(STDOUT, "%", 1);
	return (1);
}

t_flags	g_flags[ARGS_COUNT] = {{"c", c}, {"s", s}, {"d", d}, {"%", percentage}};

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
		str++;
	}
	va_end(args);
	return (bytes);
}
