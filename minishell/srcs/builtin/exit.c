/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:56:07 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 19:16:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(const char *content)
{
	int	error;

	g_env.exit = 1;
	if (ft_strchr(content, ' ') != NULL)
	{
		g_env.exit_code = 0;
		write(STDERR_FILENO, "Too many arguments.", 19);
	}
	else if (content && ft_strlen(content) > 0)
	{
		g_env.exit_code = ft_getnbr((char*)content, &error);
		if (error)
		{
			g_env.exit_code = 128;
			write(STDERR_FILENO, "Numeric argument required", 25);
		}
	}
}
