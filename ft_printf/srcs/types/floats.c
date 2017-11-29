/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:13:52 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/29 19:52:34 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/core.h"

int	ft_put_float_to_string(double nb, char **s, int precision)
{
	int		i;
	double	n;
	int		size;
	double	modulo;
	char	*str;
	int		tmp;
	int		neg;
	int		j;

	size = 1;
	neg = 0;
	if (nb < 0 && size++ && (neg = 1) == 1)
		nb = -nb;
	n = nb;
	modulo = 1;
	while ((int)(n /= 10) != 0 && size++)
		modulo *= 10;
	size += precision;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (0);
	i = 0;
	if (neg)
		str[i++] = '-';
	while ((int)nb != 0)
	{
		str[i++] = (char)((nb / modulo) + 48);
		nb -= (int)(nb / modulo) * modulo;
		modulo /= 10;
	}
	str[i++] = '.';

	nb *= 10;
	j = 0;
	while (j++ < precision)
	{
		if ((int)nb == 0)
		{
			str[i++] = '0';
			continue ;
		}
		tmp = ((int)nb != 9) ? (int)(nb + 0.01) : (int)nb;
		str[i++] = (char)(tmp + 48);
		nb = (nb - tmp) * 10;
	}

	str[i] = '\0';
	*s = str;
	return (size);
}

int	type_f(va_list args, t_flags flags)
{
	char	*nb;
	int		size;

	if (flags.precision <= 0)
		flags.precision = 7;
	size = ft_put_float_to_string(va_arg(args, double), &nb, flags.precision);
	ft_write(nb, size, flags);
	return (size);
}

int	type_f_upper(va_list args, t_flags flags) // todo: infinity...
{
	return (type_f(args, flags));
}
