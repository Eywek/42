/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <jbchoquet@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 10:16:39 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/17 11:00:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fillit.h"

int		main(int ac, char **av)
{
	int		fd;

	if (ac != 2)
	{
		ft_putstr("usage: fillit source_file\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		ft_throw_error();
	ft_display(ft_solve(ft_read_fd(fd)));
	close(fd);
	return (0);
}
