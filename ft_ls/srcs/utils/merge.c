/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:48:35 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 13:24:35 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ntsid.h>
#define MA_MIN(x) (S_ISCHR(x) || S_ISBLK(x))
#include "../../includes/ft_ls.h"

/*
 ** Add folder to folder list with the name
*/

t_dir		*ft_add_folder(const char *name)
{
	t_dir	*dir;

	if (!(dir = malloc(sizeof(t_dir))))
		ft_throw_error_memory();
	dir->name = (char*)name;
	dir->files = NULL;
	dir->next = NULL;
	return (dir);
}

/*
 ** Add file in the t_file (from a t_dir) with the current_path
*/

void		ft_add_file(t_file **files, char *filename, char *current_path)
{
	t_file	*pfiles;
	t_file	*file;

	if (!(file = malloc(sizeof(t_file))))
		return (ft_throw_error_memory());
	file->name = ft_strdup(filename);
	file->path = ft_set_path(current_path, filename);
	file->stats = ft_get_file_stats(*file);
	file->user = ft_get_user_name(file->stats.st_uid);
	file->group = ft_get_group_name(file->stats.st_gid);
	file->acl = ft_get_file_acl(*file);
	file->major = (MA_MIN(file->stats.st_mode)) ? major(file->stats.st_dev) : 0;
	file->minor = (MA_MIN(file->stats.st_mode)) ? minor(file->stats.st_dev) : 0;
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

/*
 ** Add the default folder with current path
*/

void		ft_add_default_folder(t_options *params)
{
	if (!(params->folders = malloc(sizeof(char*) * 2)) ||
		!(params->folders[0] = malloc(sizeof(char) * 2)))
		return (ft_throw_error_memory());
	params->folders[0] = ".";
	params->folders[1] = 0;
}
