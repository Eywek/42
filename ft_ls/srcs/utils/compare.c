/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:27:50 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 20:04:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

int	ft_compare_files_mtime(t_file *file1, t_file *file2)
{
	return (file1->stats.st_mtimespec.tv_sec <
			file2->stats.st_mtimespec.tv_sec);
}

int	ft_compare_files_alpha(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name) > 0);
}
