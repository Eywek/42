/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 12:30:46 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:58:04 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../../includes/ft_ls.h"

int	ft_is_dir(char *filename)
{
	struct stat path_stat;

	stat(filename, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
