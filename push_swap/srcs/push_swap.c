/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 20:00:43 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push_swap_process(t_env *env)
{
	ft_quicksort(&env->stack_a, 0, env->stack_a_size - 1);
	ft_display_stacks(*env);
}

//int		ft_quicksort_partition(int **tab, int lower, int highter)
//{
//	int	pivot;
//	int	i;
//	int	j;
//
//	pivot = (*tab)[highter];
//	i = lower - 1;
//	j = lower;
//	while (j < highter - 1)
//	{
//		if ((*tab)[j] < pivot)
//		{
//			++i;
//			ft_swap(&(*tab)[i], &(*tab)[j]);
//		}
//		++j;
//	}
//	if (tab[highter] < tab[i + 1])
//		ft_swap(&(*tab)[i + 1], &(*tab)[highter]);
//	return (i + 1);
//}
//
//void	ft_quicksort(int **tab, int lower, int highter)
//{
//	int	partition;
//
//	if (lower < highter)
//	{
//		partition = ft_quicksort_partition(tab, lower, highter);
//		ft_quicksort(tab, lower, partition - 1);
//		ft_quicksort(tab, partition + 1, highter);
//	}
//}

int		ft_quicksort_partition(int **tab, int lower, int highter)
{
	int	pivot;
	int	i;
	int	j;

	pivot = (*tab)[lower];
	i = lower - 1;
	j = highter + 1;
	while (42)
	{
		while ((*tab)[i] < pivot)
			++i;
		while ((*tab)[j] > pivot)
			--j;
		if (i >= j)
			return (j);
		ft_swap(&(*tab)[i], &(*tab)[j]);
	}
}

void	ft_quicksort(int **tab, int lower, int highter)
{
	int	partition;

	if (lower < highter)
	{
		partition = ft_quicksort_partition(tab, lower, highter);
		ft_quicksort(tab, lower, partition);
		ft_quicksort(tab, partition + 1, highter);
	}
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
