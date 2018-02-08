/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:24:29 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:25:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *g_errors[1] = {
        ERROR_GNL
};

void    ft_display_error(int code)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, g_errors[code], ft_strlen(g_errors[code]));
}

void    ft_display_prompt()
{
    ft_printf("{cyan}%s {blue}>{eoc} ", ft_get_env("USER"));
}