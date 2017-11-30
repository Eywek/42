/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:58:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 16:04:26 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

t_color	g_colors[3] = {
	{"{eoc}", "\033[0m"}, {"{cyan}", "\033[0;36m"}, {"{red}", "\033[0;31m"}
};

int	ft_handle_colors(char **str, int size, t_flags *flags, int max)
{
	int		i;
	char	*start;
	size_t	color_name_size;

	i = -1;
	while (++i < 3)
		if ((start = ft_strnstr(*str, g_colors[i].name, (size_t)max)) != 0)
		{
			color_name_size = ft_strlen(g_colors[i].name);
			ft_write(*str, (int)(start - *str), flags);
			ft_write(g_colors[i].format, (int)ft_strlen(g_colors[i].format),
					 flags);
			size -= (int)(start - *str) + color_name_size;
			*str += (start + color_name_size) - *str;
		}
	return (size);
}
