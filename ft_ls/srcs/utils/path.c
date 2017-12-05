/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:35:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 15:52:36 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/ft_ls.h"

char	*ft_set_path(char *path, const char *add)
{
	size_t	size;
	char	*tmp;
	int		add_sep;

	if (!path)
		return ((char*)add);
	if ((size = ft_strlen(path)) > 0)
	{
		tmp = path;
		add_sep = path[size - 1] != *DIRECTORY_SEPARATOR;
		path = ft_strjoin(path, add ? DIRECTORY_SEPARATOR : "");
		if (tmp[0] != '.' && tmp[1] != 0 && add_sep)
			free(tmp);
	}
	path = ft_strjoin(path, add);
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
