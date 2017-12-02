/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:20:29 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 17:46:07 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include "../includes/ft_ls.h"

t_dir	*ft_add_folder(t_dir **dirs, const char *name)
{
	t_dir	*dir;
	t_dir	*ptr;

	if (!(dir = malloc(sizeof(t_dir))))
		ft_throw_error_memory();
	dir->name = (char*)name;
	if (!(dir->files = malloc(sizeof(t_file))))
		ft_throw_error_memory();
	dir->files = NULL;
	ptr = *dirs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = dir;
	return (dir);
}

void	ft_add_file(t_file **files, char *filename, char *current_path)
{
	t_file	*pfiles;
	t_file	*file;

	if (!(file = malloc(sizeof(t_file))))
		return (ft_throw_error_memory());
	file->name = ft_strdup(filename);
	file->path = ft_set_path(current_path, filename);
	file->stats = ft_get_file_stats(*file);
	file->next = NULL;
	if (!*files)
	{
		*files = file;
		return ;
	}
	pfiles = *files;
	while (pfiles->next)
		pfiles = pfiles->next;
	pfiles->next = file;
}

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

void	ft_handle_folder(const char *name, t_dir **dirs, t_options params)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file			*files;
	t_dir			*folder;
	char			*path;

	(void)params;
	files = NULL;
	path = ft_strdup(name);
	if (!(dir = opendir(name)))
		return (ft_throw_failed_open_dir(name));
	folder = ft_add_folder(dirs, name);
	while ((entry = readdir(dir)))
		ft_add_file(&files, entry->d_name, path);
	folder->files = files;
	folder->next = NULL;
	closedir(dir);
	free(path);
}

t_dir	*ft_find_files(t_options params)
{
	t_dir	*dirs;

	dirs = NULL;
	ft_handle_files_params(params.files, &dirs);
	ft_free_tab(params.files);
	while (params.folders && *(params.folders))
		ft_handle_folder(*(params.folders++), &dirs, params);
	ft_free_tab(params.folders);
	return (dirs);
}
