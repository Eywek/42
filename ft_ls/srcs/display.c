/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:18:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/04 15:12:32 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_display_file(t_file *file, t_options params)
{
	(void)params;
	ft_printf("%s\n", file->name);
}

void	ft_display_files(t_file *files, t_options params)
{
	t_file	*ptr;

	ptr = files;
	while (ptr)
	{
		ft_display_file(ptr, params);
		ptr = ptr->next;
	}
}

void	ft_display_dir(t_dir *dir, t_options params)
{
	if (params.display_dirs || params.recursive)
		ft_printf("%c%s:\n", (params.dirs_count > 1 ? '\n' : 0), dir->name);
	ft_display_files(dir->files, params);
}
