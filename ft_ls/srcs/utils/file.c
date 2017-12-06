/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:35:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 13:26:46 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
# include <sys/xattr.h>
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

ssize_t		ft_get_file_acl(t_file file)
{
	char	*filename;
	char	name[256];
	ssize_t	res;

	if (S_ISLNK(file.stats.st_mode))
		filename = ft_get_link_path(file.path);
	else
		filename = file.path;
	ft_memset(name, 0, 256);
	listxattr(filename, name, sizeof(name), 0);
	res = getxattr(filename, name, 0, 0, 0, 0);
	if (S_ISLNK(file.stats.st_mode))
		free(filename);
	return (res);
}
