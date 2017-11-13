/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 21:01:47 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/08 13:27:04 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;

	if (!(dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (NULL);
	dup = ft_strcpy(dup, str);
	return (dup);
}
