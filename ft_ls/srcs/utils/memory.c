/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:50:15 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 16:16:48 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft_ls.h"

void	ft_free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
		free(*(tab++));
}

void	ft_copy_tab(char ***tab, char **ref)
{
	char	**ptr;

	ptr = *tab;
	if (!ref)
	{
		(*tab)[0] = 0;
		return ;
	}
	while (*ref)
		*(ptr++) = *(ref++);
}
