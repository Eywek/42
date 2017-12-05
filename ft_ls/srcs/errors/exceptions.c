/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:38:58 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 14:56:06 by vtouffet         ###   ########.fr       */
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

void	ft_throw_error_options(char option)
{
	ft_putstr_fd("ft_ls: illegal option -- ", STD_ERR);
	ft_putchar_fd(option, STD_ERR);
	ft_putchar_fd('\n', STD_ERR);
	ft_usage();
	exit(EXIT_FAILURE);
}

void	ft_throw_error_files_not_found(char **files, t_options *params)
{
	ft_sort_wordtab(files);
	while (*files)
	{
		ft_putstr_fd("ft_ls: ", STD_ERR);
		ft_putstr_fd(*files, STD_ERR);
		ft_putstr_fd(": No such file or directory\n", STD_ERR);
		files++;
	}
	params->status = EXIT_FAILURE;
}

void	ft_throw_error_fts_open(void)
{
	ft_putstr_fd("ft_ls: ", STD_ERR);
	ft_putstr_fd("fts_open", STD_ERR);
	ft_putstr_fd(": No such file or directory\n", STD_ERR);
	exit(EXIT_FAILURE);
}

void	ft_throw_failed_open_dir(const char *dirname, t_options *params)
{
	if (params->display_dirs || (params->recursive && params->dirs_count > 1))
	{
		if (params->dirs_count > 1)
			ft_putchar_fd('\n', STD_ERR);
		ft_putstr_fd(dirname, STD_ERR);
		ft_putstr_fd(":\n", STD_ERR);
	}
	ft_putstr_fd("ft_ls: ", STD_ERR);
	ft_putstr_fd(dirname, STD_ERR);
	ft_putstr_fd(": Permission denied\n", STD_ERR);
	params->status = EXIT_FAILURE;
}
