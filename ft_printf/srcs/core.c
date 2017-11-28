/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 12:59:23 by vtouffet         ###   ########.fr       */
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
		{'c', flag_c}, {'C', flag_C}, {'s', flag_s}, {'S', flag_s},
		{'d', flag_d}, {'i', flag_d}, {'%', flag_percentage}, {'p', flag_p},
		{'o', flag_o}, {'x', flag_x}, {'X', flag_X}, {'u', flag_u},
		{'D', flag_D}, {'O', flag_O}, {'U', flag_U}, {'a', flag_a},
		{'A', flag_A}
};

/*
 ** Retrieve and call the function from the name
 ** Use the t_types struct to get callback from name
*/

int	ft_call_function_from_name(char **str, va_list args, t_flags flags)
{
	char *ptr;
	int i;
	int size;

	i = 0;
	size = 1;
	ptr = *str;
	while (*ptr)
	{
		if (i > ARGS_COUNT)
		{
			if ((ft_isalpha(*ptr) && *ptr != 'h' && *ptr != 'l' && *ptr != 'j' && *ptr != 'z') || (*ptr == '}' || *ptr == '{'))
			{
				size = 1;
				if (!flags.minus)
					size = ft_pad(flags, size);
				write(STDOUT, &(*ptr), 1);
				if (flags.minus)
					size = ft_pad(flags, size);
				*str += 1;
				return (size);
			}
			++size;
			ptr++;
			i = 0;
		}
		if (*ptr == g_types[i].name)
		{
			*str += size;
			flags.type = g_types[i].name;
			return (g_types[i].f(args, flags));
		}
		++i;
	}
	*str = ptr;
	return (-1);
}

/*
 ** Call all subfonctions to init t_flags struct
 ** Format: %[parameter][flags][width][.precision][length]type
*/
/*
int	ft_handle(char **str, va_list args)
{
	t_flags		flags;
	int 		bytes;

	ft_init_flags(&flags);
	ft_handle_length(str, &flags);
	while (ft_handle_flags(str, &flags));
	while (ft_handle_width(str, &flags, args));
	ft_handle_precision(str, &flags, args);
	while (ft_handle_flags(str, &flags));
	ft_handle_length(str, &flags);
	if ((bytes = ft_call_function_from_name(str, args, flags)) > 0)
		return (bytes);
	return (0);
}
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
