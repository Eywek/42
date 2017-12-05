/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:35:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 16:31:28 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include "../../includes/ft_ls.h"

int			ft_is_file(char *filename)
{
	char		*link_path;
	struct stat	path_stat;

	lstat(filename, &path_stat);
	if (S_ISREG(path_stat.st_mode) || !path_stat.st_mode)
		return (1);
	else if (S_ISLNK(path_stat.st_mode))
	{
		link_path = ft_get_link_path(filename);
		if (ft_is_file(link_path))
		{
			free(link_path);
			return (1);
		}
		free(link_path);
	}
	return (0);
}

int			ft_is_file_or_dir(char *filename)
{
	struct stat path_stat;

	lstat(filename, &path_stat);
	return (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode) ||
			S_ISLNK(path_stat.st_mode));
}

struct stat	ft_get_file_stats(t_file file)
{
	struct stat path_stat;

	lstat(file.path, &path_stat);
	return (path_stat);
}

char		*ft_get_user_name(uid_t id)
{
	struct passwd *pwd;

	if (!(pwd = getpwuid(id)))
		return (ft_itoa(id));
	return (ft_strdup(pwd->pw_name));
}

char		*ft_get_group_name(gid_t id)
{
	struct group *grp;

	if (!(grp = getgrgid(id)))
		return (ft_itoa(id));
	return (ft_strdup(grp->gr_name));
}
