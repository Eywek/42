/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:47:25 by vtouffet          #+#    #+#             */
/*   Updated: 2018/01/11 17:32:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_push_tab(int **tab1, int *size1, int **tab2, int *size2)
{
	int	*tmp;

	if (!(tmp = malloc(sizeof(int) * (*size1 + 1))))
		ft_checker_error();
	ft_copy_tab(tmp, *tab1, *size1);
	free(*tab1);
	*tab1 = tmp;
	(*size2)--;
	ft_push(&((*tab2)[*size2]), &((*tab1)[(*size1)++]));
}

void	ft_operate(char *operation, t_env *env)
{
	if (ft_strncmp(operation, "sa", 2) == 0 && env->stack_a_size >= 2)
		ft_swap(&(env->stack_a[env->stack_a_size - 1]),
				&(env->stack_a[env->stack_a_size - 2]));
	else if (ft_strncmp(operation, "sb", 2) == 0 && env->stack_b_size >= 2)
		ft_swap(&(env->stack_b[env->stack_a_size - 1]),
				&(env->stack_b[env->stack_a_size - 2]));
	else if (ft_strncmp(operation, "pa", 2) == 0 && env->stack_b_size >= 1)
		ft_push_tab(&env->stack_a, &env->stack_a_size,
				&env->stack_b, &env->stack_b_size);
	else if (ft_strncmp(operation, "pb", 2) == 0 && env->stack_a_size >= 1)
		ft_push_tab(&env->stack_b, &env->stack_b_size,
				&env->stack_a, &env->stack_a_size);
	else if (ft_strncmp(operation, "ra", 2) == 0)
		ft_move_tab(&env->stack_a, env->stack_a_size, 1);
	else if (ft_strncmp(operation, "rb", 2) == 0)
		ft_move_tab(&env->stack_b, env->stack_b_size, 1);
	else if (ft_strncmp(operation, "rra", 3) == 0)
		ft_move_tab(&env->stack_a, env->stack_a_size, -1);
	else if (ft_strncmp(operation, "rrb", 3) == 0)
		ft_move_tab(&env->stack_b, env->stack_b_size, -1);
	if (env->verbose > 0)
	{
		ft_putstr(" === SORTING '");
		ft_putstr(operation);
		ft_putendl("' === ");
		ft_display_stacks(*env);
	}
}
