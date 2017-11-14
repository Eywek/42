/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:17:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 13:18:32 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../includes/fdf.h"

t_list	*ft_read(const char *filename)
{
	t_list	*lines;
	char	*line;
	int		fd;
	//t_list	*tmp;

	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putstr("line");
		/*tmp = ft_lstnew(ft_strsplit(line, ' '), sizeof(char**));
		if (lines)
			ft_lstaddend(&lines, tmp);
		else
			ft_lstadd(&lines, tmp);*/
	}
	exit(0);
	return (lines);
}
