/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_order.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 10:25:03 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/09 10:25:03 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

int		ft_checker_check(t_env env)
{
	int	i;

	if (env.stack_b_size > 0)
		return (0);
	i = 0;
	while (i < env.stack_a_size - 1)
	{
		if (env.stack_a[i] < env.stack_a[i + 1])
			return (0);
		++i;
	}
	return (1);
}
