/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 17:13:42 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/stat.h>
#include "../../includes/minishell.h"

static void	ft_go(const char *path)
{
	char *tmp;
	char *tmp_path;

	chdir(path);
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

static char	*ft_generate_path(const char *path, int f_links)
{
	char	*tmp;
	char	buf[PATH_MAX + 1];

	if ((tmp = ft_pathabs(path, buf, !f_links ? ft_get_env("PWD") : NULL)))
		return (ft_strdup(tmp));
	return (ft_strdup(path));
}

/*
** Options: -P -L
**
** -P: use the physical directory structure without following symbolic links
** -L: force symbolic links to be followed
**
** The default is to follow symbolic links, as if `-L' were specified.
*/

void		ft_cd(const char *content) // TODO: handle ~
{
	char	*path;
	int		follow_links;
	char	*err;

	follow_links = 0;
	if (!content || !content[0])
		return (ft_go(ft_get_env("HOME")));
	if (content[0] == '-' && content[1])
	{
		while (*content == ' ')
			++content;
		while (*(++content - 1) != ' ')
			if (*content == 'P')
				follow_links = 1;
	}
	if ((err = ft_path_error(content)))
	{
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, content, ft_strlen(content));
		return ((void)write(STDERR_FILENO, "\n", (g_env.exit_code = 1)));
	}
	path = ft_strcmp(content, "-") == 0 ? ft_strdup(ft_get_env("OLDPWD")) :
			ft_generate_path(content, follow_links);
	ft_go(path);
	free(path);
}
