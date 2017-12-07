/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:35:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <sys/xattr.h>
#include <sys/acl.h>
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

char		ft_get_file_acl(t_file file)
{
	int		xattrs;
	acl_t	acl;

	xattrs = (int)listxattr(file.path, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		return ('@');
	else
	{
		acl = acl_get_file(file.path, ACL_TYPE_EXTENDED);
		if (acl != NULL)
			return ('+');
		else
			return (' ');
	}
}
