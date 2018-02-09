/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:45 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/09 13:21:05 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unsetenv(const char *content)
{
	t_shell_env	*before;
	t_shell_env	*ptr;

	if (ft_strcmp(g_env.shell_env->name, content) == 0)
	{
		before = g_env.shell_env;
		g_env.shell_env = g_env.shell_env->next;
		free_env(before);
		return ;
	}
	ptr = g_env.shell_env;
	before = ptr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, content) == 0)
		{
			before->next = ptr->next;
			free_env(ptr);
			return ;
		}
		before = ptr;
		ptr = ptr->next;
	}
}
