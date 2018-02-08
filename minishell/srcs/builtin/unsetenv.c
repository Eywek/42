/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:45 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:36:17 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unsetenv(const char *content)
{
	t_shell_env	*before;
	t_shell_env	*ptr;

	ptr = g_env.shell_env;
	before = ptr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, content) == 0)
		{
			before->next = ptr->next;
			free(ptr);
			return ;
		}
		before = ptr;
		ptr = ptr->next;
	}
}
