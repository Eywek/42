/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:30:46 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int	ft_is_dir(char *filename)
{
	struct stat path_stat;

	lstat(filename, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	ft_can_browse(t_file file)
{
	return (S_ISDIR(file.stats.st_mode) && ft_strcmp(file.name, "..") != 0 &&
			ft_strcmp(file.name, ".") != 0);
}

int	ft_is_file_or_dir(char *filename)
{
	struct stat path_stat;

	lstat(filename, &path_stat);
	return (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode) ||
			S_ISLNK(path_stat.st_mode));
}
