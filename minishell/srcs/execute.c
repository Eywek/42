/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:30 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 18:20:15 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_make_env(void)
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

static char	**ft_generate_args(const char *args)
{
	char **tab;

	tab = ft_strsplit(args, ' ');
	if (tab && tab[0])
		return (tab);
	free(tab);
	if (!(tab = malloc(sizeof(char*) * 2)))
		ft_display_error(1);
	if (!(tab[0] = malloc(sizeof(char))))
		ft_display_error(1);
	tab[0][0] = 0;
	tab[1] = 0;
	return (tab);
}

void	ft_launch(const char *path, const char *args)
{
	char	**env;
	char	**tab;
	pid_t	pid;

	env = ft_make_env();
	tab = ft_generate_args(args);
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

void	ft_execute(const char *cmd, const char *args)
{
	char	**paths;
	int		i;
	char	*path;
	char	*tmp;
	int		ret;

	paths = ft_strsplit(ft_get_env("PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if ((ret = access(path, X_OK)) == 0) // TODO: Check if is executable
			ft_launch(path, args);
		free(path);
		free(tmp);
		free(paths[i]);
		if (ret == 0) {
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return ;
		}
	}
	free(paths);
	ft_display_error(3);
}
