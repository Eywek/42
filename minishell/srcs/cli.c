/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:14:36 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:23:53 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_builtin g_builtins[BUILTINS_COUNT] = {
        {"cd", &ft_cd}, {"echo", &ft_echo}, {"env", &ft_env},
        {"exit", &ft_exit}, {"setenv", &ft_setenv}, {"unsetenv", &ft_unsetenv},
};

void    ft_execute(const char *cmd, const char *args)
{
    (void)cmd;
    (void)args;
    ft_printf("Try to find executable in $PATH\n");
}

void    ft_parse_input(char *line)
{
    int     i;
    char    *cmd;
    char    *space_pos;

    i = -1;
    if ((space_pos = ft_strchr(line, ' ')))
        cmd = ft_strsub(line, 0, space_pos - line);
    else
        cmd = ft_strdup(line);
    while (++i < BUILTINS_COUNT)
        if (ft_strcmp(g_builtins[i].name, cmd) == 0)
            return g_builtins[i].f(line + ft_strlen(g_builtins[i].name) + 1);
    ft_execute(cmd, line + ft_strlen(cmd) + 1);
    free(cmd);
}

void    ft_wait_input()
{
    char    *line;

    while (42)
    {
        ft_display_prompt();
        if (get_next_line(STDIN_FILENO, &line) <= 0)
            ft_display_error(0);
        if (line && line[0])
            ft_parse_input(line);
        free(line);
    }
}

void    ft_handle_env(char **env)
{
    g_env.shell_env = env;
}

int     main(int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;
    ft_handle_env(env);
    ft_wait_input();
}