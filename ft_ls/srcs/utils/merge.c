/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:48:35 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/04 12:48:52 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft_ls.h"

/*
 ** Add folder to folder list with the name
*/

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
	dir->next = NULL;
	ptr = *dirs;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = dir;
	return (dir);
}

/*
 ** Add file in the t_file (from a t_dir) with the current_path
*/

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
