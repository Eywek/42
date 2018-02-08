/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:13:27 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	ft_edit_length_type(char **str, t_flags *flags, int flag_type, int size)
{
	*str += size;
	if (flags->length_type < flag_type)
		flags->length_type = flag_type;
}
