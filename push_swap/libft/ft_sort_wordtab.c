/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_wordtab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 13:08:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 17:11:58 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_str(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

void		ft_sort_wordtab(char **tab)
{
	int		index;
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		index = 0;
		while (tab[index])
		{
			if (tab[index + 1] && ft_strcmp(tab[index], tab[index + 1]) > 0)
				ft_swap_str(&tab[index], &tab[index + 1]);
			++index;
		}
		++i;
	}
}
