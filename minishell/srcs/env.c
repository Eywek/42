/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:41:48 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_get_kv(char *line, char **key, char **value)
{
    size_t  equal_pos;

    equal_pos = ft_strchr(line, '=') - line;
    *key = ft_strdup(line);
    (*key)[equal_pos] = 0;
    if (value)
        *value = line + equal_pos + 1;
}

int        ft_set_env(const char *name, const char *value)
{
    int     i;
    char    *key;
    char    *tmp;

    i = -1;
    while (g_env.shell_env[++i]) {
        ft_get_kv(g_env.shell_env[i], &key, NULL);
        if (ft_strcmp(key, name) == 0) {
            tmp = g_env.shell_env[i];
            g_env.shell_env[i] = ft_strjoin(key, "=");
            free(tmp);
            tmp = g_env.shell_env[i];
            g_env.shell_env[i] = ft_strjoin(g_env.shell_env[i], value);
            free(key);
            free(tmp);
            return (1);
        }
        free(key);
    }
    return (0);
}

char        *ft_get_env(const char *name)
{
    int     i;
    char    *key;
    char    *value;

    i = -1;
    while (g_env.shell_env[++i]) {
        ft_get_kv(g_env.shell_env[i], &key, &value);
        if (ft_strcmp(key, name) == 0) {
            free(key);
            return (value);
        }
        free(key);
    }
    return (NULL);
}