/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:48:10 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 14:46:33 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	type_a(va_list args, t_flags flags)
{
	int	*tab;
	int	index;
	int	size;

	(void)flags;
	size = 0;
	tab = va_arg(args, int*);
	index = -1;
	while (tab[++index])
	{
		size += write(STDOUT, "array[", 6);
		ft_putnbr_fd(index, STDOUT);
		ft_get_number_size_u((uintmax_t)index, 10, &size);
		size += write(STDOUT, "] = ", 4);
		if (ft_isprint(tab[index]))
			size += write(STDOUT, &tab[index], 1);
		else
		{
			ft_get_number_size_u((uintmax_t)(tab[index] < 0 ? -tab[index] :
											tab[index]), 10, &size);
			ft_putnbr_fd(tab[index], STDOUT);
		}
		size += write(STDOUT, "\n", 1);
	}
	return (size);
}

int	type_a_upper(va_list args, t_flags flags)
{
	char	**tab;
	int		index;
	int		size;

	(void)flags;
	size = 0;
	tab = va_arg(args, char**);
	index = 0;
	while (tab[index])
	{
		size += write(STDOUT, "array[", 6);
		ft_putnbr_fd(index, STDOUT);
		ft_get_number_size_u((uintmax_t)index, 10, &size);
		size += write(STDOUT, "] = \"", 5);
		size += write(STDOUT, tab[index], ft_strlen(tab[index]));
		size += write(STDOUT, "\"\n", 2);
		++index;
	}
	return (size);
}
