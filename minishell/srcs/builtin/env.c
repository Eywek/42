/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:56 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 13:25:03 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(const char *content)
{
	t_shell_env *ptr;
	int			add;

	while (content && *content)
	{
		if ((add = ft_strncmp(content, "-u", 2) == 0) ||
				ft_strncmp(content, "--unset", 7) == 0)
			return ft_unsetenv((char*)(content + (add ? 3 : 8)));
		else if ((add = ft_strncmp(content, "-i", 2) == 0) ||
				ft_strncmp(content, "--ignore-environment", 20) == 0)
		{
			g_env.exec_with_env = 0;
			return (ft_parse_input((char *) (content + (add ? 3 : 21))));
		}
		++content;
	}
	ptr = g_env.shell_env;
	while (ptr)
	{
		ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
