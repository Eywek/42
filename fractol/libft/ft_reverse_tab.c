/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:49:36 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/03 16:54:03 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_reverse_tab(char **tab)
{
	int		i;
	int		size;
	char	*tmp;

	size = 0;
	while (tab && tab[size])
		size++;
	i = 0;
	while (i < size / 2)
	{
		tmp = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = tmp;
		++i;
	}
}
