/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:48:10 by valentin          #+#    #+#             */
/*   Updated: 2017/11/26 19:05:34 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int flag_a(va_list args, t_flags flags)
{
	int	*tab;
	int	index;
	int size;

	(void)flags;
	size = 0;
	tab = va_arg(args, int*);
	index = 0;
	while (tab[index])
	{
		write(STDOUT, "array[", 6);
		ft_putnbr_fd(index, STDOUT);
		write(STDOUT, "] = ", 4);
		if (ft_isprint(tab[index]))
		{
			size += 1;
			write(STDOUT, &tab[index], 1);
		}
		else
		{
			ft_get_number_size_u((uintmax_t)(tab[index] < 0 ? -tab[index] :
											 tab[index]), 10, &size);
			ft_putnbr_fd(tab[index], STDOUT);
		}
		write(STDOUT, "\n", 1);
		size += 11;
		++index;
	}
	return (size);
}

int flag_A(va_list args, t_flags flags)
{
	char	**tab;
	int		index;
	int 	size;

	(void)flags;
	size = 0;
	tab = va_arg(args, char**);
	index = 0;
	while (tab[index])
	{
		write(STDOUT, "array[", 6);
		ft_putnbr_fd(index, STDOUT);
		write(STDOUT, "] = \"", 5);
		size += ft_strlen(tab[index]);
		write(STDOUT, tab[index], ft_strlen(tab[index]));
		write(STDOUT, "\"\n", 2);
		size += 13;
		++index;
	}
	return (size);
}
