/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:32 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:35:54 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_setenv(const char *content)
{
	char	*key;
	char	*value;
	size_t	space_pos;

	if (!content || !content[0])
		return (ft_env(content));
	space_pos = ft_strchr(content, ' ') - content;
	key = ft_strdup(content);
	key[space_pos] = 0;
	if (space_pos)
		value = (char*)content + space_pos + 1;
	else
		value = NULL;
	ft_set_env(ft_strdup(key), ft_strdup(value));
	free(key);
}
