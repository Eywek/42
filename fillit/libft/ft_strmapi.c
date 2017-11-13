/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:04:11 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/08 23:01:18 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dest;
	char	*mapi;

	i = 0;
	mapi = NULL;
	dest = NULL;
	if (s || f)
	{
		if (!(dest = ft_strnew(ft_strlen(s))))
			return (NULL);
		mapi = dest;
		if (s && f)
			while (s[i])
			{
				*dest++ = f(i, (char)s[i]);
				i++;
			}
	}
	return (mapi);
}
