/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 18:27:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 18:45:46 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	ft_write(char *str, int size, t_flags flags)
{
	*(flags.string) = ft_strcat(*(flags.string), ft_strsub(str, 0, (size_t)size));
	return (size);
	//return (int)write(STDOUT, str, (size_t)size);
}
