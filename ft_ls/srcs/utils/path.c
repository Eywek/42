/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:35:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/ft_ls.h"

char	*ft_set_path(char *path, const char *add)
{
	size_t	size;
	char	*tmp;

	if (!path)
		return (ft_strdup(add));
	tmp = 0;
	if ((size = ft_strlen(path)) > 0)
	{
		path = ft_strjoin(path, path[size - 1] != *DIRECTORY_SEPARATOR ?
				DIRECTORY_SEPARATOR : "");
		tmp = path;
	}
	path = ft_strjoin(path, add);
	if (tmp)
		free(tmp);
	return (path);
}

char	*ft_get_link_path(char *path)
{
	char		result[256];
	ssize_t		ret;

	ret = readlink(path, result, 256);
	result[ret] = 0;
	return (ft_strdup(result));
}
