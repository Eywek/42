/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 11:34:04 by exam              #+#    #+#             */
/*   Updated: 2018/02/12 17:21:22 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		is_separator(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		++i;
	}
	return (0);
}

static int		count_words(char *str, const char *charset)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str && str[i] && is_separator(str[i], charset))
		++i;
	if (str && str[i] && !is_separator(str[i], charset))
		count = 1;
	while (str && str[i])
	{
		if (!is_separator(str[i], charset) && (i > 0 &&
				is_separator(str[i - 1], charset)))
			++count;
		++i;
	}
	return (count);
}

static int		word_size(char *str, char const *charset)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (str && str[i] && !is_separator(str[i], charset))
	{
		++size;
		++i;
	}
	return (size);
}

char			**ft_strsplitchrset(char *str, const char *charset,
									const char *first)
{
	char	**tab;
	int		i;
	int		j;
	int		index;

	if (!(tab = (char**)malloc(sizeof(char*) *
					(count_words(str, charset) + 1 + (first != NULL)))))
		return (NULL);
	i = -1;
	index = -1;
	if (first && (tab[++index] = malloc(sizeof(char) * (ft_strlen(first) + 1))))
		ft_strcpy(tab[index], first);
	while (str && str[++i])
		if (!is_separator(str[i], charset))
		{
			if (((index == -1 || (index == 0 && first)) || (i > 0 &&
					is_separator(str[i - 1], charset))) && (j = 0) == 0)
				if (!(tab[++index] = (char*)malloc(sizeof(char) * (word_size(
						str + i, charset) + 1))))
					return (NULL);
			tab[index][j] = str[i];
			tab[index][++j] = '\0';
		}
	tab[++index] = 0;
	return (tab);
}
