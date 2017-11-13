/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 10:16:39 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/12 17:58:22 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fillit.h"

int		main(int ac, char **av)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (ac != 2 && fd == -1)
		ft_putstr("usage: fillit source_file\n");
	else
		ft_display(ft_solve(ft_read_fd(fd)));
	close(fd);
	return (0);
}
