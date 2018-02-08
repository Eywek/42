/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 16:53:30 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:33:57 by vtouffet         ###   ########.fr       */
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

void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, proc_signal_handler);
	}
}

void	ft_launch(const char *path, const char *args)
{
	char	**env;
	int		i;
	pid_t	pid;

	ft_printf("Launch %s with '%s'\n", path, args);
	env = ft_make_env();
	pid = fork();
	signal(SIGINT, proc_signal_handler);
	if (pid == 0)
		execve(path, ft_strsplit(args, ' '), env);
	else if (pid < 0)
		ft_display_error(2);
	wait(&pid);
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
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
		if ((ret = access(path, X_OK)) == 0)
			ft_launch(path, args);
		free(path);
		free(tmp);
		free(paths[i]);
		if (ret == 0)
			break ;
	}
	free(paths);
	if (access(cmd, X_OK))
		ft_launch(cmd, args);
	else
		ft_display_error(3);
}
