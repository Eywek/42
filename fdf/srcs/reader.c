/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 12:30:47 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_list	*ft_read(char *filename)
{
	t_list	*lines;
	char	*line;
	int		fd;
	t_list	*tmp;

	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		tmp = ft_lstnew(ft_strsplit(line, ' '), sizeof(char**));
		if (*line)
			ft_lstaddend(&lines, tmp);
		else
			lines = tmp;
	}
	return (lines);
}
