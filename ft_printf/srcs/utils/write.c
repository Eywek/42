/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:27:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 20:07:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../../includes/core.h"

int	ft_write(void *s, int size, t_flags flags)
{
	//*(flags.string) = ft_strjoin(*(flags.string), ft_strsub(str, 0, (size_t)size));
	char	*src;
	char	*str;
	int		previous_size;
	int 	i;

	//printf("START APPEND '%s' OF %d\n", s, size);
	previous_size = *(flags.bytes);
	//printf(" - ACTUAL STRING '%s' (%d) -> malloc = %d\n", *(flags.string), *(flags.bytes), previous_size + size + 1);
	str = (char *)malloc(sizeof(char) * (previous_size + size + 1));
	if (str == NULL)
		return (-1);
	ft_strcpy(str, *(flags.string));
	//printf(" - AFTER COPY '%s'\n", str);
	i = 0;
	src = s;
	while (i < size)
	{
		//printf(" - PUT str[%d] = src[%d] = %c\n", previous_size, i, src[i]);
		str[previous_size++] = src[i++];
	}
	str[previous_size] = '\0';
	//printf(" - AFTER COPY 2 '%s'\n", str);

	free(*(flags.string));
	*(flags.string) = str;



	*(flags.bytes) += size;
	return (size);
}
