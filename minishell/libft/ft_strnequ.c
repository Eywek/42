/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 14:02:51 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/11 16:43:56 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (!s1 || !s2)
		return (s1 == s2 ? 1 : 0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	if (ft_strlen((char*)s1) != ft_strlen((char*)s2) && i < n)
		return (0);
	return (1);
}
