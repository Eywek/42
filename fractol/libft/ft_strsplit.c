/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:00:53 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/09 12:14:55 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	*charset;
	char	**tab;

	if (!s || !c)
		return (NULL);
	if (!(charset = ft_strnew(2)))
		return (NULL);
	charset[0] = c;
	tab = ft_strsplitchrset((char*)s, charset, NULL);
	free(charset);
	return (tab);
}
