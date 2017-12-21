/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/21 16:27:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_do_operate(char *operation, t_env *env, int *state)
{
	ft_operate(operation, env);
	ft_lstaddend(&env->operations, ft_lstnew(operation, ft_strlen(operation)));
	*state = 1;
}

int		ft_get_index_inf(t_env env)
{
	int	i;
	int	pos;
	int	min_value;

	i = -1;
	pos = 0;
	min_value = env.stack_a[0];
	while (++i < env.stack_a_size)
	{
		if (min_value < env.stack_a[i])
		{
			min_value = env.stack_a[i];
			pos = i;
		}
	}
	return (pos);
}

int		ft_can_push(t_env env)
{
	int	search;
	int	i;

	search = env.stack_a[env.stack_a_size - 1];
	i = env.stack_a_size - 1;
	while (i >= 0)
	{
		if (env.stack_a[i] < search)
			return (0);
		--i;
	}
	return (1);
}

int		ft_order_reverse(t_env *env)
{
	int	is_reversed;
	int	i;
	int	sorting;

	is_reversed = 1;
	i = -1;
	while (++i < env->stack_a_size - 1)
	{
		if (env->stack_a[i] > env->stack_a[i + 1])
			is_reversed = 0;
	}
	if (!is_reversed)
		return (0);
	i = 0;
	while (!ft_checker_check_b(*env) || !ft_checker_check_a(*env))
	{
		if (i++ > 0)
			ft_do_operate("pb", env, &sorting);
		ft_do_operate("rra", env, &sorting);
	}
	return (1);
}

void	ft_sort(t_env *env)
{
	int	sorting;
	int	pos;

	sorting = 0;
	while (!ft_checker_check_b(*env) || !ft_checker_check_a(*env))
	{
		if (ft_order_reverse(env))
			break ;
		if (env->stack_a_size > 1 && env->stack_a[env->stack_a_size - 1] > env->stack_a[env->stack_a_size - 2])
			ft_do_operate("sa", env, &sorting);
		if (ft_can_push(*env))
		{
			ft_do_operate("pb", env, &sorting);
			continue ;
		}
		pos = (env->stack_a_size - 1) - ft_get_index_inf(*env);
		if (pos >= 0)
		{
			sorting = 0;
			if (pos >= (env->stack_a_size / 2) && env->stack_a_size > 1)
				while (pos++ < env->stack_a_size)
					ft_do_operate("rra", env, &sorting);
			else
				while (pos-- >= 0)
					ft_do_operate("ra", env, &sorting);
			if (sorting)
				continue ;
		}
	}
	while (env->stack_b_size > 0)
		ft_do_operate("pa", env, &sorting);
}

void	ft_push_swap_process(t_env *env)
{
	ft_putendl(" === BEFORE === ");
	ft_display_stacks(*env);
	if (!ft_checker_check(*env))
		ft_sort(env);
	ft_putendl(" === SORTED === ");
	ft_display_stacks(*env);
	ft_putendl(" ==== OPERATIONS ====");
	ft_display_operations(*env); // TODO: Malloc directement stack_b de la taille de stack_a
}

int		main(int argc, char *argv[])
{
	t_env	env;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (!(env.stack_a = malloc(sizeof(int))) ||
		!(env.stack_b = malloc(sizeof(int))))
		ft_checker_error();
	ft_memset(&env, 0, sizeof(env));
	ft_checker_handle_stack(argc, argv, &env);
	ft_push_swap_process(&env);
	//free(env.stack_a);
	//free(env.stack_b);
	return (EXIT_SUCCESS);
}
