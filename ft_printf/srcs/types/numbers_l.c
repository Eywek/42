/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:18:26 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 21:17:45 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int flag_D(va_list args, t_flags flags)
{
	flags.length_type = LENGTH_L;
	return (flag_d(args, flags));
}

int flag_O(va_list args, t_flags flags)
{
	flags.length_type = LENGTH_L;
	return (flag_o(args, flags));
}

int flag_U(va_list args, t_flags flags)
{
	flags.length_type = LENGTH_L;
	return (flag_u(args, flags));
}
