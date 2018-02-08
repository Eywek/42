/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:56 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:07:04 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env(const char *content)
{
    int i;

    (void)content;
    i = 0;
    while (g_env.shell_env[i])
        ft_printf("%s\n", g_env.shell_env[i++]);
}