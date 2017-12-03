/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:07:24 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/03 17:08:05 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

struct stat	ft_get_stats_from_name(char *name)
{
	t_file	file;

	file.path = name;
	return (ft_get_file_stats(file));
}
