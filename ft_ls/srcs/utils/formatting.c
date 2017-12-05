/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:34:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 12:48:42 by vtouffet         ###   ########.fr       */
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
