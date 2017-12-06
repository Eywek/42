/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_columns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:18:20 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 19:09:34 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	ft_display_columns(t_file *file, t_options params, t_display *datas)
{
//	int			elements_count;
//	static int	count = 0;
//
//	(void)params;
//	count++;
//	elements_count = (ft_get_window_width() % datas.name_len) / 2;
//	elements_count += (elements_count % 2) ? 1 : 0;
//	if (count < elements_count)
//		ft_display_name("%-*s", datas.name_len + 1, *file, params);
//	else
//	{
//		ft_display_name("%s\n", 0, *file, params);
//		count = 0;
//	}
	int			width;

	(void)params;
	width = ft_get_window_width();
	if (datas->c_count + datas->name_len + 1 > width)
	{
		datas->c_count = 1;
		ft_display_name("\n%-*s", datas->name_len + 1, *file, params);
	}
	else
		ft_display_name("%-*s", datas->name_len + 1, *file, params);
	datas->c_count += datas->name_len + 1;
}
