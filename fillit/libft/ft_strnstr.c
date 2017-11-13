/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 23:19:40 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/06 17:07:36 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t n)
{
	size_t	len_td;

	len_td = ft_strlen(tofind);
	if (!*tofind)
		return ((char *)str);
	while (*str && n-- >= len_td)
	{
		if (*str == *tofind && ft_memcmp(str, tofind, len_td) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
