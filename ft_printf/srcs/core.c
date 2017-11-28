/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 13:05:27 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/core.h"

/*
 ** List of all types and callbacks
 ** /s /S /p /d /D /i /o /O /u /U /x /X /c /C /%
 ** flag to display tabs
*/

t_types	g_types[ARGS_COUNT] = {
		{'c', type_c}, {'C', type_C}, {'s', type_s}, {'S', type_s},
		{'d', type_d}, {'i', type_d}, {'%', type_percentage}, {'p', type_p},
		{'o', type_o}, {'x', type_x}, {'X', type_X}, {'u', type_u},
		{'D', type_D}, {'O', type_O}, {'U', type_U}, {'a', type_a},
		{'A', type_A}
};

/*
 ** Call the type with the current char, using the g_types array
 ** Display some padding if the char isn't a valid type
*/

int	ft_call_type(char **str, va_list args, t_flags flags)
{
	int arg;
	int size;

	arg = 0;
	while (arg < ARGS_COUNT)
	{
		if (**str == g_types[arg].name)
		{
			*str += 1;
			flags.type = g_types[arg].name;
			return (g_types[arg].f(args, flags));
		}
		arg++;
	}
	size = 1;
	if (!flags.minus)
		size = ft_pad(flags, size);
	write(STDOUT, *str, 1);
	if (flags.minus)
		size = ft_pad(flags, size);
	*str += 1;
	return (size);
}

/*
 ** Try to apply all length modifiers / flags / width / precision
 ** Then, try to call a type
 ** Stop the process if the next char is the end of the string or if we found
 ** a stranger char
*/

int	ft_handle(char **str, va_list args)
{
	t_flags		flags;
	int 		bytes;
	int 		flags_found;

	ft_init_flags(&flags);
	while (**str)
	{
		flags_found = 0;
		while (ft_handle_length(str, &flags) ||
				ft_handle_flags(str, &flags) ||
				ft_handle_width(str, &flags, args) ||
				ft_handle_precision(str, &flags, args))
			flags_found = 1;
		if (flags.precision > 0 || flags.precision == -1)
			flags.zero = 0;
		if (ft_isalpha(**str) || **str == '%')
		{
			if ((bytes = ft_call_type(str, args, flags)) > -1)
				return (bytes);
		}
		else if (!*(*str + 1) || !flags_found)
			return (0);
	}
	return (0);
}

/*
 ** First function :
 ** start stdarg,
 ** process format with ft_handle if it's a % or display char
 ** Sources:
 **  https://cdn.intra.42.fr/pdf/pdf/20/ft_printf.pdf
 **  https://en.wikipedia.org/wiki/Printf_format_string
 **  https://msdn.microsoft.com/fr-fr/library/hf4y5e3w.aspx
 **  https://www.lix.polytechnique.fr/~liberti/public/computing/prog/c/C/FUNCTIONS/format.html
 **  http://www.cplusplus.com/reference/cstdio/printf/
 **  http://manpagesfr.free.fr/man/man3/printf.3.html
*/

int	ft_printf(const char *restrict format, ...) // TODO: unicode
{
	char	*str;
	int		bytes;
	va_list args;
	size_t 	next;

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
			if (ft_strchr(str, '%'))
				next = ft_strchr(str, '%') - str;
			else
				next = ft_strlen(str);
			write(STDOUT, str, next);
			bytes += next;
			str += next;
		}
	}
	va_end(args);
	return (bytes);
}
