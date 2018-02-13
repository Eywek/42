/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:14:36 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 19:11:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_builtin	g_builtins[BUILTINS_COUNT] =
{
	{"cd", &ft_cd},
	{"echo", &ft_echo},
	{"env", &ft_env},
	{"exit", &ft_exit},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
};

void		ft_parse_input(char *line)
{
	int		i;
	char	*cmd;
	char	*space_pos;
	char	*arg;

	i = -1;
	if ((space_pos = ft_strchr(line, ' ')))
		cmd = ft_strsub(line, 0, space_pos - line);
	else
		cmd = ft_strdup(line);
	arg = (ft_strlen(line) > ft_strlen(cmd) + 1) ?
		line + ft_strlen(cmd) + 1 : "";
	while (++i < BUILTINS_COUNT)
		if (ft_strcmp(g_builtins[i].name, cmd) == 0)
		{
			free(cmd);
			return (g_builtins[i].f(arg));
		}
	ft_execute(cmd, arg);
	free(cmd);
}

void		ft_wait_input(void)
{
	char	*line;

	while (42)
	{
		ft_display_prompt();
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			exit(0);//ft_display_error(0);
		if (line && line[0])
			ft_parse_input(line);
		free(line);
		if (g_env.exit)
		{
			ft_free_env(g_env.shell_env);
			exit(g_env.exit_code);
		}
	}
}

void		ft_handle_env(char **env)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (env[++i])
	{
		ft_get_kv(env[i], &key, &value);
		ft_set_env(key, value, 0);
	}
}

int			main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	ft_memset(&g_env, 0, sizeof(g_env));
	ft_handle_env(env);
	ft_wait_input();
}
