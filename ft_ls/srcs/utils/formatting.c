/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 17:34:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/04 18:14:42 by vtouffet         ###   ########.fr       */
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
	if (date < now && now - date >= (3600 * 24 * 30.5 * 6))
		write(1, s + 19, 5);
	else
		write(1, s + 11, 5);
}
