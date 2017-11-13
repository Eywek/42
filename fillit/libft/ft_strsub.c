/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:58:17 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/09 11:20:03 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = NULL;
	if (s)
	{
		if (!(sub = ft_strnew(len)))
			return (NULL);
		while (start--)
			s++;
		sub = ft_strncpy(sub, s, len);
	}
	return (sub);
}
