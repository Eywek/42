/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:11 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 17:26:45 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(const char *content)
{
	write(STDIN_FILENO, content, ft_strlen(content));
	write(STDIN_FILENO, "\n", 1);
}
