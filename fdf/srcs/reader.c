/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 14:13:58 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_list	*ft_read(const char *filename)
{
	t_list	*lines;
	t_line	*content;
	char	*line;
	int		fd;
	t_list        *tmp;

	lines = NULL;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(content = malloc(sizeof(t_line))))
			ft_throw_error();
		content->content = ft_strsplit(line, ' ');
		if (!(tmp = ft_lstnew(content, sizeof(t_line))))
			ft_throw_error();
		if (lines)
			ft_lstaddend(&lines, tmp);
		else
			ft_lstadd(&lines, tmp);
	}
	return (lines);
}
