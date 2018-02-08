/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:58:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

t_color	g_colors[COLOR_COUNT] = {
	{"{eoc}", "\033[0m"}, {"{black}", "\033[0;30m"}, {"{red}", "\033[0;31m"},
	{"{green}", "\033[0;32m"}, {"{orange}", "\033[0;33m"},
	{"{blue}", "\033[0;34m"}, {"{purple}", "\033[0;35m"},
	{"{cyan}", "\033[0;36m"}, {"{light_gray}", "\033[0;37m"},
	{"{dark_gray}", "\033[1;30m"}, {"{light_red}", "\033[1;31m"},
	{"{light_green}", "\033[1;32m"}, {"{yellow}", "\033[1;33m"},
	{"{light_blue}", "\033[1;34m"}, {"{light_purple}", "\033[1;35m"},
	{"{light_cyan}", "\033[1;36m"}, {"{white}", "\033[1;37m"},
};

int	ft_handle_colors(char **str, int size, t_flags *flags, int max)
{
	int		i;
	char	*start;
	size_t	color_name_size;

	i = -1;
	while (++i < COLOR_COUNT)
		if ((start = ft_strnstr(*str, g_colors[i].name, (size_t)max)) != 0)
		{
			color_name_size = ft_strlen(g_colors[i].name);
			size = ft_handle_colors(str, size, flags, (int)(start - *str));
			ft_write(*str, (int)(start - *str), flags);
			size -= (int)(start - *str) + color_name_size;
			*str += (start + color_name_size) - *str;
			ft_write(g_colors[i].format, (int)ft_strlen(g_colors[i].format),
					flags);
			i--;
		}
	return (size);
}
