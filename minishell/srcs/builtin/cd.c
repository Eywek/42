/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:34:27 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(const char *content)
{
	if (chdir(content) == -1)
		ft_printf("cd: no such file or directory: %s\n", content);
}
