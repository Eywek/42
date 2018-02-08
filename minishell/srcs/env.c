/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 16:17:19 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void                ft_get_kv(char *line, char **key, char **value)
{
    size_t  equal_pos;

    equal_pos = ft_strchr(line, '=') - line;
    *key = ft_strdup(line);
    (*key)[equal_pos] = 0;
    *value = ft_strdup(line + equal_pos + 1);
}

static t_shell_env  *ft_add_env_element(const char *name, const char *value)
{
    t_shell_env *ptr;

    if (!(ptr = malloc(sizeof(t_shell_env))))
        ft_display_error(1);
    ptr->name = (char*)name;
    ptr->value = (char*)value;
    ptr->next = NULL;
    return (ptr);
}

int                 ft_set_env(const char *name, const char *value)
{
    t_shell_env *ptr;

    ptr = g_env.shell_env;
    if (!ptr) {
        g_env.shell_env = ft_add_env_element(name, value);
        return (1);
    }
    while (ptr->next) {
        if (ft_strcmp(ptr->name, name) == 0) {
            free(ptr->value);
            ptr->value = ft_strdup(value);
            return (0);
        }
        ptr = ptr->next;
    }
    ptr->next = ft_add_env_element(name, value);
    return (1);
}

char                *ft_get_env(const char *name)
{
    t_shell_env *ptr;

    ptr = g_env.shell_env;
    while (ptr) {
        if (ft_strcmp(ptr->name, name) == 0)
            return (ptr->value);
        ptr = ptr->next;
    }
    return (NULL);
}