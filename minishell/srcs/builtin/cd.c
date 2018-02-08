/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 18:00:22 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_go(const char *path)
{
	if (chdir(path) == 0)
	{
		ft_set_env("OLDPWD", ft_get_env("PWD"));
		ft_set_env("PWD", path);
	}
	else
		ft_printf("cd: no such file or directory: %s\n", path);
}

static char	*ft_generate_path(const char *path)
{
	return ((char*)path); // TODO: Check /
}

void		ft_cd(const char *content)
{
	if (!content || !content[0])
		ft_go(ft_get_env("HOME"));
	else if (ft_strcmp(content, "-") == 0)
		ft_go(ft_get_env("OLDPWD"));
	else
		ft_go(ft_generate_path(content));
}
