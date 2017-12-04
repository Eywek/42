/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:20:29 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/04 13:20:12 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "../includes/ft_ls.h"

/*
 ** Add files (from t_options) to the first dir
*/

void	ft_handle_files_params(char **files_list, t_dir **dirs)
{
	t_file	*files;
	char	*path;

	if (!(*dirs = malloc(sizeof(t_dir))))
		return (ft_throw_error_memory());
	(*dirs)->name = NULL;
	if (!(files = malloc(sizeof(t_file))))
		return (ft_throw_error_memory());
	files = NULL;
	path = ft_strdup("");
	while (files_list && *files_list)
	{
		ft_add_file(&files, *files_list, path);
		files_list++;
	}
	(*dirs)->files = files;
	(*dirs)->next = NULL;
	free(path);
}

/*
 ** Recursive function to find files in folders
*/

void	ft_recursive(char *path, t_dir **dirs, t_options params)
{
	t_file	*files;
	t_file	*file;

	files = (*dirs)->files;
	file = files;
	while (file)
	{
		if (S_ISDIR(file->stats.st_mode))
			ft_handle_folder(ft_set_path(path, file->name), dirs, params);
		file = file->next;
	}
}

/*
 ** Find files in folders
*/

void	ft_handle_folder(char *path, t_dir **dirs, t_options params)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*files;
	t_dir			*folder;

	files = NULL;
	if (!(dir = opendir(path)))
		return (ft_throw_failed_open_dir(path));
	folder = ft_add_folder(dirs, path);
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.' || params.hidden_files)
			ft_add_file(&files, entry->d_name, path);
	}
	if (params.sort_by_time)
		ft_sort_files(&files, &ft_compare_files_mtime);
	else
		ft_sort_files(&files, &ft_compare_files_alpha);
	if (params.sort_reverse)
		ft_sort_files_reverse(&files);
	folder->files = files;
	closedir(dir);
	ft_display_dir(folder, params);
	if (params.recursive)
		ft_recursive(path, &folder, params);
}

/*
 ** Main function which find files and folders in t_options
*/

t_dir	*ft_find_files(t_options params)
{
	t_dir	*dirs;

	dirs = NULL;
	ft_handle_files_params(params.files, &dirs);
	ft_display_files(dirs->files, params);
	ft_free_tab(params.files);
	while (params.folders && *(params.folders))
	{
		ft_handle_folder(*(params.folders), &dirs, params);
		params.folders++;
	}
	ft_free_tab(params.folders);
	return (dirs);
}
