/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 16:23:51 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 16:29:23 by vtouffet         ###   ########.fr       */
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
	ft_printf("params.folders : \n%A\n", params.folders);
	ft_printf("params.files : \n%A\n", params.files);
}

void	ft_debug_dirs(t_dir *dirs)
{
	while (dirs)
	{
		ft_printf("dirs.name = %s\n", dirs->name);
		while (dirs->files)
		{
			ft_printf(" - dirs.files.name = %s\n", dirs->files->name);
			dirs->files = dirs->files->next;
		}
		dirs = dirs->next;
	}
}
