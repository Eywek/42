/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:50:15 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft_ls.h"

void	ft_free_tab(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
		free(*(tab++));
}

void	ft_copy_tab(char ***tab, char **ref)
{
	char	**ptr;

	ptr = *tab;
	if (!ref)
	{
		(*tab)[0] = 0;
		return ;
	}
	while (*ref)
		*(ptr++) = *(ref++);
}

void	ft_remove_files(t_file **files_list)
{
	t_file	*files;
	t_file	*next;

	files = *files_list;
	while (files)
	{
		next = files->next;
		free(files->group);
		free(files->name);
		free(files->path);
		free(files->user);
		free(files);
		files = next;
	}
	*files_list = NULL;
}

void	ft_remove_dir(t_dir **dir)
{
	t_dir	*tmp;
	t_file	*files;

	free((*dir)->name);
	files = (*dir)->files;
	ft_remove_files(&files);
	tmp = (*dir)->next;
	free(*dir);
	*dir = tmp;
}
