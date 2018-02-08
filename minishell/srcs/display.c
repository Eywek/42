/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:24:29 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:33:11 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*g_errors[4] =
{
	ERROR_GNL,
	ERROR_MALLOC,
	ERROR_EXEC,
	ERROR_CMD_NOT_FOUND
};

void	ft_display_error(int code)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, g_errors[code], ft_strlen(g_errors[code]));
	if (code == 1)
		exit(1);
}

void	ft_display_prompt(void)
{
	ft_printf("{cyan}%s {blue}>{eoc} ", ft_get_env("PWD"));
}
