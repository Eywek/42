/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 19:48:21 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/07 16:59:39 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	cur;

	cur = 0;
	while (src[cur] && cur < n)
	{
		dest[cur] = src[cur];
		cur++;
	}
	while (cur < n)
		dest[cur++] = '\0';
	return (dest);
}
