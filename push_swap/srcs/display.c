/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:45:16 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/22 15:58:37 by valentin         ###   ########.fr       */
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
	if (ft_strcmp(lst->content, "sa") == 0)
		write(1, "\033[0;32m", 7);
	else if (ft_strcmp(lst->content, "ra") == 0)
		write(1, "\033[0;33m", 7);
	else if (ft_strcmp(lst->content, "rra") == 0)
		write(1, "\033[1;33m", 7);
	else if (ft_strcmp(lst->content, "pa") == 0)
		write(1, "\033[0;35m", 7);
	else if (ft_strcmp(lst->content, "pb") == 0)
		write(1, "\033[0;36m", 7);
	write(1, lst->content, lst->content_size);
	write(1, "\n", 1);
	return (lst);
}

void	ft_display_operations(t_env env)
{
	ft_lstmap(env.operations, &ft_display_operation);
}

void	ft_checker_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}
