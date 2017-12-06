/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_columns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:18:20 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/06 19:38:36 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void	ft_display_columns(t_file *file, t_options params, t_display *datas)
{
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
