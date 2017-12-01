/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:35:39 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:40:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../../includes/ft_ls.h"

int	ft_is_file(char *filename)
{
	struct stat path_stat;
	stat(filename, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int	ft_is_file_or_dir(char *filename)
{
	struct stat path_stat;
	stat(filename, &path_stat);
	return (S_ISREG(path_stat.st_mode) || S_ISDIR(path_stat.st_mode));
}
