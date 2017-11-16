/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:06:10 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/16 15:50:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "get_next_line.h"
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	char	*line;
	int		fd;

	fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_putstr(line);
		ft_putchar('\n');
	}
	return 0;
}
