/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 18:07:14 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 17:46:19 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	ft_free_env(void)
{
	t_shell_env	*ptr;
	t_shell_env	*tmp;

	ptr = g_env.shell_env;
	while (ptr)
	{
		tmp = ptr->next;
		ft_free_env_el(ptr);
		ptr = tmp;
	}
	g_env.shell_env = NULL;
}

int		ft_is_exec(char *path)
{
	struct stat path_stat;

	if (lstat(path, &path_stat) == -1)
		return (0);
	if (!S_ISREG(path_stat.st_mode) && !S_ISLNK(path_stat.st_mode))
		return (0);
	return (path_stat.st_mode & S_IXUSR ? 1 : -1);
}

char	*ft_get_link_path(char *path)
{
	struct stat path_stat;
	char		result[256];
	ssize_t		ret;

	if (lstat(path, &path_stat) == -1 || !S_ISLNK(path_stat.st_mode))
		return (ft_strdup(path));
	ret = readlink(path, result, 256);
	result[ret] = 0;
	return (ft_strdup(result));
}

void	ft_free_env_el(t_shell_env *el)
{
	free(el->name);
	if (el->value)
		free(el->value);
	free(el);
}
