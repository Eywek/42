/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:57:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 18:10:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ft_ls.h"

void	ft_display_file_permissions(t_file *file)
{
	ft_printf("%c", ft_file_type(file->stats.st_mode));
	ft_printf((file->stats.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWUSR) ? "w" : "-");
	if (file->stats.st_mode & S_ISUID)
		ft_printf(file->stats.st_mode & S_IXUSR ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWGRP) ? "w" : "-");
	if (file->stats.st_mode & S_ISGID)
		ft_printf(file->stats.st_mode & S_IXGRP ? "s" : "S");
	else
		ft_printf((file->stats.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((file->stats.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((file->stats.st_mode & S_IWOTH) ? "w" : "-");
	if (file->stats.st_mode & S_ISVTX)
		ft_printf(file->stats.st_mode & S_IXOTH ? "t" : "T");
	else
		ft_printf((file->stats.st_mode & S_IXOTH) ? "x" : "-");
	ft_printf("%c", ft_get_file_acl(*file));
}

void	ft_display_long_file(t_file *file, t_options params, t_display datas)
{
	char	*link_path;
	char	*path;

	ft_display_file_permissions(file);
	ft_printf("%*lld %-*s %-*s ",
				datas.link_len + 1, file->stats.st_nlink,
				datas.user_len + 1, file->user,
				datas.group_len + 1, file->group);
	if (file->major == -1 && file->minor == -1)
		ft_printf("%*lld ", datas.size_len, file->stats.st_size);
	else
		ft_printf("%*d, %*d ", datas.major_len, file->major,
					datas.minor_len, file->minor);
	ft_display_format_time(file->stats.st_mtime);
	if (S_ISLNK(file->stats.st_mode))
	{
		path = ft_set_path(params.current_path, file->name);
		link_path = ft_get_link_path(path);
		free(path);
		ft_display_name(" %s", 0, *file, params);
		ft_printf(" -> %s\n", link_path);
		free(link_path);
	}
	else
		ft_display_name(" %s\n", 0, *file, params);
}
