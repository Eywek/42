/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 12:19:21 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/09 11:19:09 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	char	*map;

	dst = NULL;
	map = NULL;
	if (s || f)
	{
		if (!(dst = ft_strnew(ft_strlen(s))))
			return (NULL);
		map = dst;
		if (s && f)
			while (*s)
				*dst++ = f((char)*s++);
	}
	return (map);
}
