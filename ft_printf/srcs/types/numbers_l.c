/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 11:18:26 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 14:01:33 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	type_d_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_d(args, flags));
}

int	type_o_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_o(args, flags));
}

int	type_u_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_u(args, flags));
}
