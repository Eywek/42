/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:38:58 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 16:58:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../includes/ft_ls.h"

void	ft_throw_error_memory(void)
{
	write(STD_ERR, "Error on memory\n", 16);
	exit(EXIT_FAILURE);
}

void	ft_throw_error_options(char *option)
{
	write(STD_ERR, "ft_ls: illegal option -- ", 25);
	write(STD_ERR, option + 1, ft_strlen(option) - 1);
	write(STD_ERR, "\n", 1);
	ft_usage();
	exit(EXIT_FAILURE);
}

void	ft_throw_error_file_not_found(char *filename)
{
	write(STD_ERR, "ft_ls: ", 7);
	write(STD_ERR, filename, ft_strlen(filename));
	write(STD_ERR, ": No such file or directory\n", 28);
}

void	ft_throw_failed_open_dir(const char *dirname)
{
	write(STD_ERR, "ft_ls: ", 7);
	write(STD_ERR, dirname, ft_strlen(dirname));
	write(STD_ERR, ": Permission denied\n", 20);
}
