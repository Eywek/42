/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:18:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "../includes/ft_ls.h"

void		ft_display_file(t_file *file, t_options params, t_display *datas)
{
	if (!params.long_format && params.no_columns)
		return (ft_display_name("%s\n", 0, *file, params));
	if (!params.long_format)
		return (ft_display_columns(file, params, datas));
	ft_display_long_file(file, params, *datas);
}

void		ft_fill_datas(t_file *file, t_display *datas)
{
	datas->link_len = ft_max(datas->link_len, ft_nbrlen(file->stats.st_nlink));
	datas->size_len = ft_max(datas->size_len,
							ft_nbrlen((uintmax_t)file->stats.st_size));
	if (file->major > -1 || file->minor > -1)
		datas->major_len = ft_max(datas->major_len,
							ft_nbrlen((uintmax_t)file->major) + 1);
	if (file->major > -1 || file->minor > -1)
		datas->minor_len = ft_max(datas->minor_len,
							ft_nbrlen((uintmax_t)file->minor));
	datas->user_len = ft_max(datas->user_len, (int)ft_strlen(file->user));
	datas->group_len = ft_max(datas->group_len, (int)ft_strlen(file->group));
	datas->name_len = ft_max(datas->name_len, (int)ft_strlen(file->name));
	datas->total_blocks += file->stats.st_blocks;
}

t_display	ft_calcul_file_datas(t_file *files)
{
	t_display	datas;
	t_file		*ptr;

	ptr = files;
	ft_memset(&datas, 0, sizeof(datas));
	while (ptr)
	{
		ft_fill_datas(ptr, &datas);
		ptr = ptr->next;
	}
	if (datas.minor_len > 0 || datas.major_len > 0)
		datas.size_len = ft_max(datas.size_len,
				(datas.major_len + datas.minor_len + 2));
	return (datas);
}

void		ft_display_files(t_file *files, t_options params)
{
	t_file		*ptr;
	t_display	datas;

	ptr = files;
	datas = ft_calcul_file_datas(files);
	if (params.long_format && ptr && params.folders)
		ft_printf("total %d\n", datas.total_blocks);
	while (ptr)
	{
		ft_display_file(ptr, params, &datas);
		ptr = ptr->next;
	}
}

void		ft_display_dir(t_dir *dir, t_options params)
{
	if (params.display_dirs || (params.recursive && params.dirs_count > 1))
	{
		if (params.dirs_count > 1)
			ft_printf("%c%s:\n", '\n', dir->name);
		else
			ft_printf("%s:\n", dir->name);
	}
	ft_display_files(dir->files, params);
	if (!params.long_format && !params.no_columns && dir->files)
		ft_printf("\n");
}
