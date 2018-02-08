/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:23:17 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_set_env(const char *name, const char *value)
{
    (void)name;
    (void)value;
}

char    *ft_get_env(const char *name)
{
    int     i;
    char    *key;
    char    *value;
    size_t  equal_pos;

    i = -1;
    while (g_env.shell_env[++i]) {
        equal_pos = ft_strchr(g_env.shell_env[i], '=') - g_env.shell_env[i];
        key = ft_strdup(g_env.shell_env[i]);
        key[equal_pos] = 0;
        value = g_env.shell_env[i] + equal_pos + 1;
        if (ft_strcmp(key, name) == 0) {
            free(key);
            return (value);
        }
        free(key);
    }
    return (NULL);
}