/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 16:05:11 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_go(const char *path)
{
	if (access(path, X_OK) != 0 || chdir(path) != 0)
		ft_printf("cd: no such file or directory: %s\n", path);
	ft_set_env("OLDPWD", ft_get_env("PWD"));
	ft_set_env("PWD", path);
}

static char	*ft_generate_path(const char *path)
{
	char	*pwd;
	char	*p;

	if (path[0] == '/')
		return ft_strdup(path);
	pwd = ft_get_env("PWD");
	if (ft_strcmp(path, "..") == 0)
		return ft_strsub(pwd, 0, ft_strrchr(pwd, '/') - pwd);
	if (!(p = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(pwd) + 2))))
		ft_display_error(1);
	ft_strcat(ft_strcat(ft_strcpy(p, pwd), "/"), path);
	return (p);
}

void		ft_cd(const char *content)
{
	char	*path;

	if (!content || !content[0])
		return (ft_go(ft_get_env("HOME")));
	else if (ft_strcmp(content, "-") == 0)
	{
		path = ft_strdup(ft_get_env("OLDPWD"));
		ft_go(path);
		free(path);
		return ;
	}
	else if (ft_strcmp(content, ".") == 0)
		return ;
	path = ft_generate_path(content);
	ft_go(path);
	free(path);
}
