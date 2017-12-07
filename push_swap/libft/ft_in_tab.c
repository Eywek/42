/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:24:06 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 15:02:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
#include <printf.h>

/* ************************************************************************** */

int	ft_in_tab(int search, int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == search)
			return (1);
		++i;
	}
	return (0);
}
