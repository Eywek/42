/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:45 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 18:40:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_unsetenv_el(char *name)
{
	t_shell_env	*before;
	t_shell_env	*ptr;

	if (ft_strcmp(g_env.shell_env->name, name) == 0)
	{
		before = g_env.shell_env;
		g_env.shell_env = g_env.shell_env->next;
		ft_free_env_el(before);
		return ;
	}
	ptr = g_env.shell_env;
	before = ptr;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, name) == 0)
		{
			before->next = ptr->next;
			ft_free_env_el(ptr);
			return ;
		}
		before = ptr;
		ptr = ptr->next;
	}
}

void		ft_unsetenv(const char *content)
{
	char		**names;
	int			i;

	names = ft_strsplitchrset((char*)content, " \n\t\v\f\r", 0);
	i = 0;
	while (names[i])
	{
		ft_unsetenv_el(names[i]);
		free(names[i++]);
	}
	free(names);
	g_env.exit_code = 0;
}
