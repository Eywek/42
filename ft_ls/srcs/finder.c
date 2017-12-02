/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 12:20:29 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 16:35:49 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

void	ft_add_file(t_file **files, char *filename)
{
	t_file	*pfiles;
	t_file	*file;

	if (!(file = malloc(sizeof(t_file))))
		return (ft_throw_error_memory());
	file->name = ft_strdup(filename);
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

	if (!(*dirs = malloc(sizeof(t_dir))))
		return (ft_throw_error_memory());
	(*dirs)->name = NULL;
	if (!(files = malloc(sizeof(t_file))))
		return (ft_throw_error_memory());
	files = NULL;
	while (files_list && *files_list)
	{
		ft_add_file(&files, *files_list);
		files_list++;
	}
	(*dirs)->files = files;
	(*dirs)->next = NULL;
}

void	ft_handle_folder(const char *name, t_dir **dirs, t_options params)
{
	(void)name;
	(void)dirs;
	(void)params;
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
