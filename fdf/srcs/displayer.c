/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 14:27:44 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_list	*ft_display_line(t_list *line)
{
	int o = 0;
	char **content = line->content;
	ft_putstr("SALUT");
	while (content[o])
		ft_putnbr(o++);
	return (line);
}

void	ft_display(t_list *lines)
{
	ft_putstr("yo");
	ft_lstmap(lines, &ft_display_line);
}
