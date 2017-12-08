/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:23:51 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	ft_debug_options(t_options params)
{
	ft_printf("params.hidden_files = %d\n", params.hidden_files);
	ft_printf("params.long_format = %d\n", params.long_format);
	ft_printf("params.recursive = %d\n", params.recursive);
	ft_printf("params.sort_by_time = %d\n", params.sort_by_time);
	ft_printf("params.reverse = %d\n", params.sort_reverse);
	ft_printf("params.no_columns = %d\n", params.no_columns);
	ft_printf("params.options_count = %d\n", params.options_count);
	ft_printf("params.display_dirs = %d\n", params.display_dirs);
	ft_printf("params.dirs_count = %d\n", params.dirs_count);
	ft_printf("params.folders : \n%A\n", params.folders);
	ft_printf("params.files : \n%A\n", params.files);
	ft_printf("params.not_founds : \n%A\n", params.not_founds);
}

void	ft_debug_file(t_file *file)
{
	ft_printf(" - dirs.files.name = %s\n", file->name);
	ft_printf("     dirs.files.size = %d\n", file->stats.st_size);
	ft_printf("     dirs.files.user = %s\n", file->user);
	ft_printf("     dirs.files.group = %s\n", file->group);
	ft_printf("     dirs.files.acl = %d\n", ft_get_file_acl(*file));
	ft_printf("     dirs.files.major = %d\n", file->major);
	ft_printf("     dirs.files.minor = %d\n", file->minor);
}

void	ft_debug_files(t_file *files)
{
	while (files)
	{
		ft_debug_file(files);
		files = files->next;
	}
}

void	ft_debug_dir(t_dir *dir)
{
	ft_printf("dirs.name = %s\n", dir->name);
	ft_debug_files(dir->files);
}

void	ft_debug_dirs(t_dir *dirs)
{
	while (dirs)
	{
		ft_debug_dir(dirs);
		dirs = dirs->next;
	}
}
