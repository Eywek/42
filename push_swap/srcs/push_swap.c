/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/08 16:17:29 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push_swap_process(t_env *env)
{
	ft_quicksort(env->stack_a, env->stack_a_size);
	ft_display_stacks(*env);
}

int		ft_quicksort_get_pivot(int *tab, int size)
{
	int	pivot_index;
	int	value;
	int	j;

	value = tab[0];
	pivot_index = 0;
	j = size;
	while (42)
	{
		++pivot_index;
		while (tab[pivot_index] < value && pivot_index < size)
			++pivot_index;
		--j;
		while (tab[j] > value)
			--j;
		if (pivot_index >= j)
			break ;
		ft_swap(&tab[pivot_index], &tab[j]);
	}
	ft_swap(&tab[pivot_index - 1], &tab[0]);
	return (pivot_index);
}

void	ft_quicksort(int *tab, int size)
{
	int	pivot_index;

	if (size <= 1)
		return ;
	pivot_index = ft_quicksort_get_pivot(tab, size);
	ft_quicksort(tab, pivot_index - 1);
	ft_quicksort(tab + pivot_index, size - pivot_index);
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
	free(env.stack_a);
	free(env.stack_b);
	return (EXIT_SUCCESS);
}
