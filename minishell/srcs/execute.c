/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:30 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/09 13:15:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_make_env(void)
{
	char		**env;
	t_shell_env	*ptr;
	int			i;
	char		*tmp;

	if (!(env = malloc(sizeof(char *) * ft_count_env())))
		ft_display_error(1);
	ptr = g_env.shell_env;
	i = -1;
	while (ptr)
	{
		tmp = ft_strjoin(ptr->name, "=");
		env[++i] = ft_strjoin(tmp, ptr->value);
		free(tmp);
		ptr = ptr->next;
	}
	env[i] = 0;
	return (env);
}

static void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, proc_signal_handler);
	}
}

static int	ft_exec(char *path, const char *cmd, const char *args)
{
	char	*tmp;
	char	*fullpath;
	int		ret;

	tmp = ft_strjoin(path, "/");
	fullpath = ft_strjoin(tmp, cmd);
	if ((ret = ft_is_exec(fullpath)) == 1)
		ft_launch(fullpath, args);
	else if (ret == -1)
		ft_display_error(4);
	free(fullpath);
	free(tmp);
	return (ret);
}

void		ft_launch(const char *path, const char *args)
{
	char	**env;
	char	**tab;
	pid_t	pid;

	env = ft_make_env();
	tab = ft_strsplitchrset((char*)args, " ", path);
	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, tab, env);
	else if (pid < 0)
		ft_display_error(2);
	wait(&pid);
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
	while (paths[++i])
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
		ft_launch(cmd, args);
	else if (ret == -1)
		ft_display_error(4);
	else
		ft_display_error(3);
}
