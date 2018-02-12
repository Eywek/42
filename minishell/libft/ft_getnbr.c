/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 00:05:26 by valentin          #+#    #+#             */
/*   Updated: 2018/02/12 18:48:51 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int    ft_getnbr(char *str, int *error)
{
	int    nb;
	int    neg;

	nb = 0;
	neg = 1;
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-')
			return (*error = 1);
		else if (*str == '-')
		{
			neg = -1;
			str++;
			continue ;
		}
		nb = nb * 10 + (*str - 48);
		if (nb > INT_MAX || nb < 0)
			return (*error = 1);
		str++;
	}
	*error = 0;
	return (nb * neg);
}
