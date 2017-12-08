/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:45:16 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/08 18:00:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_display_stacks(t_env env)
{
	int	i;

	i = 0;
	ft_putstr("STACK A:\n");
	while (i < env.stack_a_size)
	{
		ft_putnbr(env.stack_a[env.stack_a_size - 1 - i++]);
		ft_putchar('\n');
	}
	i = 0;
	ft_putstr("STACK B:\n");
	while (i < env.stack_b_size)
	{
		ft_putnbr(env.stack_b[env.stack_b_size - 1 - i++]);
		ft_putchar('\n');
	}
}

t_list	*ft_display_operation(t_list *lst)
{
	ft_putendl(lst->content);
	return (lst);
}

void	ft_display_operations(t_env env)
{
	ft_lstmap(env.operations, &ft_display_operation);
}
