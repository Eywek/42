/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:35:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 17:48:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft_ls.h"

char	*ft_set_path(char *path, const char *add)
{
	if (ft_strlen(path) > 0)
		path = ft_strjoin(path, DIRECTORY_SEPARATOR);
	path = ft_strjoin(path, add);
	return (path);
}
