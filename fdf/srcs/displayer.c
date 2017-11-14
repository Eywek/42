/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:55:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 14:08:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_throw_error(void)
{
	write(1, "Error\n", 6);
	exit(0);
}

t_list	*ft_display_line(t_list *line)
{
	int i = 0;
	char **content = ((t_line*)(line->content))->content;
	while (content[i])
		ft_putstr(content[i++]);
	ft_putchar('\n');
	return (line);
}

void	ft_display(t_list *lines)
{
	ft_lstmap(lines, &ft_display_line);
}
