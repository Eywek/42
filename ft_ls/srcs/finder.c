/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:20:29 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "../includes/ft_ls.h"

/*
 ** Add files (from t_options) to the first dir
*/

int		ft_handle_files_params(char **files_list, t_options params)
{
	t_file	*files;
	char	*path;
	int		files_count;

	path = ft_strdup("");
	files = NULL;
	files_count = 0;
	while (files_list && *files_list)
	{
		ft_add_file(&files, *files_list, path);
		files_count++;
		files_list++;
	}
	ft_sort_files(&files, &ft_compare_files_alpha);
	if (params.sort_by_time)
		ft_sort_files(&files, &ft_compare_files_mtime);
	if (params.sort_reverse)
		ft_sort_files_reverse(&files);
	ft_display_files(files, params);
	ft_remove_files(&files);
	free(path);
	ft_free_tab(params.files);
	return (files_count);
}

/*
 ** Recursive function to find files in folders
*/

void	ft_recursive(char *path, t_dir **dirs, t_options *params)
{
	t_file	*files;
	t_file	*file;
	char	*tmp;

	files = (*dirs)->files;
	file = files;
	while (file)
	{
		if (ft_can_browse(*file))
		{
			tmp = ft_set_path(path, file->name);
			ft_handle_folder(tmp, params);
			free(tmp);
		}
		file = file->next;
	}
}

/*
 ** Find files in folders
*/

void	ft_handle_folder(char *path, t_options *params)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*files;
	t_dir			*folder;

	files = NULL;
	params->current_path = path;
	if (!(dir = opendir(path)))
		return (ft_throw_failed_open_dir(path, params));
	folder = ft_add_folder(path);
	while ((entry = readdir(dir)))
		if (entry->d_name[0] != '.' || params->hidden_files)
			ft_add_file(&files, entry->d_name, path);
	ft_sort_files(&files, &ft_compare_files_alpha);
	if (params->sort_by_time)
		ft_sort_files(&files, &ft_compare_files_mtime);
	if (params->sort_reverse)
		ft_sort_files_reverse(&files);
	folder->files = files;
	closedir(dir);
	params->dirs_count++;
	ft_display_dir(folder, *params);
	if (params->recursive)
		ft_recursive(path, &folder, params);
	ft_remove_dir(&folder);
}

/*
 ** Main function which find files and folders in t_options
*/

void	ft_find_files(t_options *params)
{
	params->dirs_count = ft_handle_files_params(params->files, *params);
	while (params->folders && *(params->folders))
	{
		ft_handle_folder(*(params->folders), params);
		params->folders++;
	}
	ft_free_tab(params->folders);
	ft_free_tab(params->not_founds);
}
