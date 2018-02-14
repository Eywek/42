/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:11 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 13:06:39 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(const char *content)
{
	int	i;
	int	n;

	if (!content)
		return ;
	i = 0;
	while (content[i] && content[i] == ' ')
		++i;
	if ((n = (ft_strncmp(content + i, "-n ", 3) == 0)))
		content += i + 3;
	write(STDIN_FILENO, content, ft_strlen(content));
	if (!n)
		write(STDIN_FILENO, "\n", 1);
	g_env.exit_code = 0;
}
