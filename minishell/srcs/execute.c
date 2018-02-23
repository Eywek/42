/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:30 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 17:21:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../includes/minishell.h"

char		**ft_make_env(void)
{
	char		**env;
	t_shell_env	*ptr;
	int			i;

	if (!(env = malloc(sizeof(char *) * (ft_count_env() + 1))))
		ft_display_error(1);
	ptr = g_env.use_tmp_env ? g_env.tmp_env : g_env.shell_env;
	i = -1;
	while (ptr)
	{
		if (!(env[++i] = malloc((sizeof(char) * ft_strlen(ptr->name) +
				ft_strlen(ptr->value) + 2))))
			ft_display_error(1);
		ft_strcat(ft_strcat(ft_strcpy(env[i], ptr->name), "="), ptr->value);
		ptr = ptr->next;
	}
	env[++i] = 0;
	return (env);
}

static int	ft_exec(char *path, const char *cmd, const char *args)
{
	char	*fullpath;
	int		ret;

	if (!(fullpath = malloc(sizeof(char) *
									(ft_strlen(cmd) + ft_strlen(path) + 2))))
		ft_display_error(1);
	ft_strcat(ft_strcat(ft_strcpy(fullpath, path), "/"), cmd);
	if ((ret = ft_is_exec(fullpath)) == 1)
		ft_launch(fullpath, args);
	else if (ret == -1)
		ft_display_error(4);
	free(fullpath);
	return (ret);
}

void		ft_launch(const char *path, const char *args)
{
	char		**env;
	char		**tab;
	pid_t		pid;
	int			status;
	struct stat	s;

	if (stat(path, &s) == -1)
		return (ft_display_error((g_env.exit_code = 1) + 5));
	env = ft_make_env();
	tab = ft_strsplitchrset((char*)args, " ", path);
	g_env.is_processing = 1;
	pid = fork();
	if (pid == 0)
		execve(path, tab, env);
	else if (pid < 0)
		ft_display_error(2);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_env.exit_code = WEXITSTATUS(status);
	g_env.is_processing = 0;
	ft_free_tab(env);
	ft_free_tab(tab);
}

void		ft_execute(const char *cmd, const char *args)
{
	char	**paths;
	int		i;
	int		ret;

	paths = ft_strsplit(ft_get_env("PATH"), ':');
	i = -1;
	while (paths && paths[++i])
	{
		ret = ft_exec(paths[i], cmd, args);
		free(paths[i]);
		if (ret)
		{
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return ;
		}
	}
	free(paths);
	if ((ret = ft_is_exec((char*)cmd)) == 1)
		return (ft_launch(cmd, args));
	if (ret == -1)
		return (ft_display_error((g_env.exit_code = 127) - 123));
	ft_display_error(3);
	g_env.exit_code = 127;
}
