/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:03:21 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 17:03:21 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_getnbr(char *str, int *error)
{
	int	nb;
	int	neg;

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
