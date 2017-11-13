/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 13:56:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_display_line(t_list *line)
{
	return (line);
}

void	ft_display(t_list *lines)
{
	ft_lstmap(lines, &ft_display_line);
}
