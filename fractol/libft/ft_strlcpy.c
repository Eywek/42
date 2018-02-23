/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:35:13 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 15:35:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	char const	*sptr;
	size_t		slen;

	sptr = src;
	while (*sptr++)
		;
	slen = ((size_t)(sptr - src - 1));
	if (slen < size)
		ft_strncpy(dst, src, slen + 1);
	else if (size != 0)
	{
		ft_strncpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	return (slen);
}
