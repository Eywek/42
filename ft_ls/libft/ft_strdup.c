/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:39:19 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:50 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char const *src)
{
	char	*dup;
	size_t	sz;

	sz = ft_strlen(src);
	if (!(dup = malloc((sz + 1) * sizeof(char))))
		return (NULL);
	return (ft_strcpy(dup, src));
}
