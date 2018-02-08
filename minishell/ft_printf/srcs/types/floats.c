/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:13:52 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:32:00 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/core.h"

int	type_f(va_list args, t_flags *flags)
{
	char	*nb;
	int		size;

	if (flags->precision <= 0)
		flags->precision = 7;
	size = ft_put_float_to_string(va_arg(args, double), &nb, flags->precision);
	ft_write(nb, size, flags);
	free(nb);
	return (size);
}

int	type_f_upper(va_list args, t_flags *flags)
{
	return (type_f(args, flags));
}
