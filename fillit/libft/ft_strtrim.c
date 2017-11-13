/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:07:56 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/08 23:03:56 by jechoque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	space;
	size_t	len;

	space = 0;
	if (!s)
		return (NULL);
	while ((s[space] == '\n' || s[space] == '\t' || s[space] == ' '))
		space++;
	if (!s[space])
		return (ft_strdup(s + space));
	len = ft_strlen(s) - 1;
	while ((s[len] == '\n' || s[len] == '\t' || s[len] == ' ') && len > 0)
		len--;
	return (ft_strsub(s, space, len - space + 1));
}
