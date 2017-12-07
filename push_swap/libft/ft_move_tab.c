/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:11:20 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 18:28:20 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <printf.h>

void	ft_move_tab(int **tab, int size, int move)
{
	int	*moved;
	int	i;

	if (size == 0)
		return ;
	if (!(moved = malloc(sizeof(int) * size)))
		return ;
	i = 1;
	moved[0] = (*tab)[size - 1];
	//printf("moved[0] = %d\n", moved[0]);
	while (i < size)
	{
		moved[i] = (*tab)[i - move];
	//	printf("moved[%d] = %d\n", i, moved[i]);
		++i;
	}
	free(*tab);
	*tab = moved;
}
