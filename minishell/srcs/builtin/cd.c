/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/14 12:43:40 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/stat.h>
#include "../../includes/minishell.h"

static void	ft_go(const char *path, int f_links)
{
	char		*tmp;
	struct stat	s;
	char		*tmp_path;
	int			link;

	chdir(path);
	if ((link = (f_links && lstat(path, &s) == 0 && S_ISLNK(s.st_mode))))
		path = getcwd(ft_strnew(PATH_MAX), PATH_MAX);
	tmp = ft_strdup("OLDPWD");
	if (ft_set_env(tmp, ft_get_env("PWD"), 0) == 0)
		free(tmp);
	tmp = ft_strdup("PWD");
	tmp_path = ft_strdup(path);
	if (ft_set_env(tmp, tmp_path, 0) == 0)
	{
		free(tmp_path);
		free(tmp);
	}
	if (link)
		free((char*)path);
	g_env.exit_code = 0;
}

static char	*ft_path_error(const char *path)
{
	struct stat	s;

	if (ft_strcmp(path, "-") == 0)
		return (NULL);
	if (!*path || lstat(path, &s) < 0 != 0)
		return ("cd: No such file or directory: ");
	if (!S_ISDIR(s.st_mode) && !S_ISLNK(s.st_mode))
		return ("cd: Not a directory: ");
	if (!S_ISLNK(s.st_mode) && access(path, R_OK) != 0)
		return ("cd: Permission denied: ");
	if (stat(path, &s) == -1)
		return ("cd: Too many symbolic links: ");
	return (NULL);
}

static char	*ft_generate_path(const char *path)
{
	char		*tmp;
	char		buf[PATH_MAX + 1];

	if ((tmp = ft_pathabs(path, buf, ft_get_env("PWD"))))
		return (ft_strdup(tmp));
	return (ft_strdup(path));
}

static char	*ft_handle_tilde(const char *path)
{
	char	*new;

	if (path[0] != '~')
		return (ft_strdup(path));
	if (!(new = malloc(sizeof(char) * (ft_strlen(ft_get_env("HOME")) +
			ft_strlen(path)))))
		ft_display_error(1);
	ft_strcpy(new, ft_get_env("HOME"));
	ft_strcat(new, path + 1);
	return (new);
}

/*
** Options: -P -L
**
** -P: use the physical directory structure without following symbolic links
** -L: force symbolic links to be followed
**
** The default is to follow symbolic links, as if `-L' were specified.
*/

void		ft_cd(const char *content)
{
	char	*path;
	char	*p;
	int		follow_links;
	char	*err;

	if ((follow_links = 0) == 0 && content && content[0] == '-' && content[1])
	{
		while (*content == ' ')
			++content;
		while (*content && *(++content - 1) != ' ')
			if (*content == 'P')
				follow_links = 1;
	}
	if (!content || !content[0])
		return (ft_go(ft_get_env("HOME"), follow_links));
	p = ft_handle_tilde(content);
	if ((err = ft_path_error(p)))
	{
		ft_display_error_msg(err, content);
		return ((void)(g_env.exit_code = 1));
	}
	ft_go((path = ft_strcmp(content, "-") == 0 ? ft_strdup(ft_get_env("OLDPWD"))
			: ft_generate_path(p)), follow_links);
	free(path);
	free(p);
}
