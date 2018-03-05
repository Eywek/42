/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:14:36 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/14 14:59:29 by vtouffet         ###   ########.fr       */
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
	while (*line == ' ' || *line == '\t')
		line++;
	if (!*line)
		return ;
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

static void	proc_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr("\n");
		g_env.exit_code = 130;
		if (!g_env.is_processing)
			ft_display_prompt();
		signal(SIGINT, proc_signal_handler);
	}
}

void		ft_wait_input(void)
{
	char	*line;
	char	**cmds;
	int		i;

	signal(SIGINT, proc_signal_handler);
	while (42)
	{
		ft_display_prompt();
		if (get_next_line(STDIN_FILENO, &line) <= 0)
			exit(g_env.exit_code);
		if (line && line[0])
		{
			cmds = ft_strsplit(line, ';');
			i = 0;
			while (cmds && cmds[i])
				ft_parse_input(cmds[i++]);
			ft_free_tab(cmds);
		}
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
		free(key);
		free(value);
	}
}

/*
** BONUS:
** - Gestion du signal CTRL+C -> OUI / NON
** - Gestion des commandes avec les ';' -> OUI / NON
** - Droits d'execution dans le path -> OUI / NON
** - Prompt affichant le pwd
** - Gestion de la tilde dans le cd
** - Gestion du env -i / -u
** - Gestion du -P sur cd
** - Gestion du echo -n
** - Couleur qui change sur le prompt selon la dernière commande
*/

int			main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	ft_memset(&g_env, 0, sizeof(g_env));
	ft_handle_env(env);
	ft_wait_input();
	return (0);
}
