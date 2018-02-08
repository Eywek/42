/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:56 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:35:04 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(const char *content)
{
	t_shell_env *ptr;

	(void)content;
	ptr = g_env.shell_env;
	while (ptr)
	{
		ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}
