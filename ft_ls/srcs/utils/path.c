/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:35:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 13:58:27 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/ft_ls.h"

char	*ft_set_path(char *path, const char *add)
{
	size_t	size;

	if (!path)
		return ((char*)add);
	if ((size = ft_strlen(path)) > 0) // TODO: free old path, free old strjoin
		path = ft_strjoin(path, path[size - 1] != *DIRECTORY_SEPARATOR ? DIRECTORY_SEPARATOR : "");
	path = ft_strjoin(path, add);
	return (path);
}

char	*ft_get_link_path(char *path)
{
	char		result[256];
	ssize_t		ret;

	ret = readlink(path, result, 256);
	result[ret] = 0;
	return (ft_strdup(result)); // TODO: free
}
