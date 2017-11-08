/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:06:10 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/08 17:45:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char	*line;
	int		fd;

	fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	printf("read = %d\n", get_next_line(fd, &line));
	printf("content = '%s'\n", line);
	printf("read = %d\n", get_next_line(fd, &line));
	printf("content = '%s'\n", line);
	printf("read = %d\n", get_next_line(fd, &line));
	printf("content = '%s'\n", line);
	printf("read = %d\n", get_next_line(fd, &line));
	printf("content = '%s'\n", line);
	printf("read = %d\n", get_next_line(fd, &line));
	return 0;
}
