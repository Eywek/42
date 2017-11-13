/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:22:58 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 16:51:41 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar(*str++);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i++]);
	return (i - 1);
}

int		brackets(char *str)
{
	char	list[4096];
	char	*ptr;

	list[0] = '\0';
	ptr = list;
	while (*str)
	{
		if (*str == '(' || *str == '[' || *str == '{')
			*(ptr++) = *str;
		else if (*str == ')')
		{
			if (ft_strlen(list) > 0 && *(ptr - 1) == '(')
				*(--ptr) = '\0';
			else
				return (0);
		}
		else if (*str == ']')
		{
			if (ft_strlen(list) > 0 && *(ptr - 1) == '[')
				*(--ptr) = '\0';
			else
				return (0);
		}
		else if (*str == '}')
		{
			if (ft_strlen(list) > 0 && *(ptr - 1) == '{')
				*(--ptr) = '\0';
			else
				return (0);
		}
		++str;
	}
	return (ft_strlen(list) <= 0);
}

int		main(int argc, const char *argv[])
{
	int	count;

	count = 0;
	if (argc > 1)
	{
		while (count++ < argc - 1)
		{
			if (brackets((char*)argv[1]))
				ft_putstr("OK");
			else
				ft_putstr("Error");
			ft_putchar('\n');
		}
	}
	else
		ft_putchar('\n');
	return 0;
}
