/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 11:18:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/04 11:23:38 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_display_files(t_file *files)
{
	t_file	*ptr;

	ptr = files;
	while (ptr)
	{
		ft_printf("%s\n", ptr->name);
		ptr = ptr->next;
	}
}

void	ft_display_dir(t_dir *dir)
{
	ft_printf("%s:\n", dir->name);
	ft_display_files(dir->files);
}
