/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:30:46 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/03 14:20:29 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int	ft_is_dir(char *filename)
{
	struct stat path_stat;

	stat(filename, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_can_browse(struct dirent entry)
{
	return (entry.d_type == DT_DIR && ft_strcmp(entry.d_name, "..") != 0 &&
			ft_strcmp(entry.d_name, ".") != 0);
}
