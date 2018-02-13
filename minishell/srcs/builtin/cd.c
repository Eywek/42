/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 19:25:59 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_go(const char *path)
{
	char *tmp;
	char *tmpPath;

	if (access(path, X_OK) != 0 || chdir(path) != 0) // TODO: NOT A DIRECTORY / PERMISSION DENIED
	{
		write(STDERR_FILENO, "cd: no such file or directory: ", 31);
		write(STDERR_FILENO, path, ft_strlen(path));
		write(STDERR_FILENO, "\n", 1);
		g_env.exit_code = 1;
		return ;
	}
	tmp = ft_strdup("OLDPWD");
	if (ft_set_env(tmp, ft_get_env("PWD"), 0) == 0)
		free(tmp);
	tmp = ft_strdup("PWD");
	tmpPath = ft_strdup(path);
	if (ft_set_env(tmp, tmpPath, 0) == 0)
	{
		free(tmpPath);
		free(tmp);
	}
}

static char	*ft_links(const char *path, int follow_links)
{
	char	*tmp;

	if (follow_links)
	{
		tmp = (char*)path;
		path = ft_get_link_path((char*)path);
		free(tmp);
	}
	return ((char*)path);
}

static char	*ft_remove_useless_slashs(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	while (path[--i] == '/' && i > 0)
		path[i] = 0;
	return (path);
}

static char	*ft_generate_path(const char *path, int follow_links)
{
	char	*pwd;
	char	*p;

	if (path[0] == '/')
		return (ft_strdup(path));
	pwd = ft_get_env("PWD");
	if (ft_strcmp(path, "..") == 0)
		return (ft_strsub(pwd, 0, ft_strrchr(pwd, '/') - pwd));
	if (!(p = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(pwd) + 2))))
		ft_display_error(1);
	ft_strcat(ft_strcat(ft_strcpy(p, pwd), "/"), path);
	return (ft_links(p, follow_links));
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
	int		follow_links;

	follow_links = 0;
	if (!content || !content[0] || ft_strcmp(content, ".") == 0)
		return (ft_strcmp(content, ".") == 0 ? "" : ft_go(ft_get_env("HOME")));
	if (content[0] == '-' && content[1])
	{
		while (*content == ' ')
			++content;
		while (*(++content - 1) != ' ')
			if (*content == 'P')
				follow_links = 1;
	}
	if (ft_strcmp(content, "-") == 0)
	{
		path = ft_strdup(ft_get_env("OLDPWD"));
		ft_go(ft_links(path, follow_links));
		free(path);
		return ;
	}
	path = ft_generate_path(content, follow_links);
	ft_go(ft_remove_useless_slashs(path));
	free(path);
}
