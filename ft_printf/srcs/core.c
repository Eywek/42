/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 21:38:41 by valentin         ###   ########.fr       */
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
		{'c', flag_c}, {'C', flag_C}, {'s', flag_s}, {'S', flag_S},
		{'d', flag_d}, {'i', flag_d}, {'%', flag_percentage}, {'p', flag_p},
		{'o', flag_o}, {'x', flag_x}, {'X', flag_X}, {'u', flag_u},
		{'D', flag_D}, {'O', flag_O}, {'U', flag_U}
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
		if (**str == ' ')
			(*str)++;
		else if (**str == g_types[i].name)
		{
			(*str)++;
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

int	ft_handle(char **str, va_list args) // Todo: Handle dynamic value for precision/width with *
{
	t_flags		flags;
	int 		bytes;

	ft_init_flags(&flags);
	ft_handle_length(str, &flags);
	while (ft_handle_flags(str, &flags));
	ft_handle_width(str, &flags);
	ft_handle_precision(str, &flags);
	ft_handle_length(str, &flags);
	if ((bytes = ft_call_function_from_name(str, args, flags)) > 0)
		return (bytes);
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
			str += 1;
		}
	}
	va_end(args);
	return (bytes);
}
