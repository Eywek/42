/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:34:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <unistd.h>
#include "../../includes/ft_ls.h"

void	ft_display_format_time(time_t date)
{
	char	*s;
	time_t	now;

	now = time(&now);
	s = ctime(&date);
	write(1, s + 4, 7);
	if (date > now)
	{
		write(1, " ", 1);
		write(1, ft_strtrim(s + 19),
				(size_t)ft_nbrlen((uintmax_t)ft_atoi(s + 19)));
	}
	else if (date < now && now - date >= (3600 * 24 * 30.5 * 6))
		write(1, s + 19, 5);
	else
		write(1, s + 11, 5);
}

char	ft_file_type(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else
		return ('-');
}

void	ft_display_name(char *format, int width, t_file file, t_options params)
{
	int	color;

	color = 0;
	if (params.colors && S_ISDIR(file.stats.st_mode))
		color = ft_printf(COLOR_FOLDER) + 1;
	else if (params.colors && S_ISLNK(file.stats.st_mode))
		color = ft_printf(COLOR_LINK) + 1;
	else if (params.colors && S_ISSOCK(file.stats.st_mode))
		color = ft_printf(COLOR_SOCKET) + 1;
	else if (params.colors && file.stats.st_mode & S_IXUSR)
		color = ft_printf(COLOR_EXECUTE) + 1;
	if (width)
		ft_printf(format, width, file.name);
	else
		ft_printf(format, file.name);
	if (color)
		ft_printf("{eoc}");
}
