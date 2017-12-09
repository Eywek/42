/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/09 10:21:44 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

//t_array	ft_merge(t_array array1, t_array array2)
//{
//	if (array1.n == 0)
//		return (array2);
//	else if (array2.n == 0)
//		return (array1);
//	else if (array1.tab[0] <= array2.tab[0])
//	{
//		array1.tab++;
//		array1.n--;
//		return (ft_merge(array1, array2));
//	}
//	else
//	{
//		array2.tab++;
//		array2.n--;
//		return (ft_merge(array1, array2));
//	}
//}
//
//t_array	ft_merge_sort(t_array array)
//{
//	t_array	array1;
//	t_array	array2;
//	int		diff;
//
//	if (array.n <= 1)
//		return (array);
//	diff = array.n / 2;
//	array1.tab = array.tab;
//	array1.n = array.n - diff;
//	array2.tab = array.tab + (diff + 1);
//	array2.n = array.n - (diff + 1);
//	return (ft_merge(ft_merge_sort(array1), ft_merge_sort(array2)));
//}

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))
//  Left run is A[iLeft :iRight-1].
// Right run is A[iRight:iEnd-1  ].
void ft_merge(int *A, int iLeft, int iRight, int iEnd, int *B, t_env *env)
{
	int	i;
	int	j;
	int	k;

	i = iLeft, j = iRight;
	// While there are elements in the left or right runs...
	for (k = iLeft; k < iEnd; k++) {
		// If left run head exists and is <= existing right run head.
		if (i < iRight && (j >= iEnd || A[i] <= A[j])) {
			B[k] = A[i];
			ft_lstaddend(&env->operations, ft_lstnew("pb", 2));
			i = i + 1;
		} else {
			B[k] = A[j];
			ft_lstaddend(&env->operations, ft_lstnew("pb", 2));
			j = j + 1;
		}
	}
}

void	ft_copy_tab_op(int *dest, int *src, int size, t_env *env)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		dest[i] = src[i];
		ft_lstaddend(&env->operations, ft_lstnew("pa", 2));
	}
}

void	ft_merge_sort(int *A, int *B, int n, t_env *env)
{
	int	width;
	int	i;

	// Each 1-element run in A is already "sorted".
	// Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted.
	for (width = 1; width < n; width = 2 * width)
	{
		// Array A is full of runs of length width.
		for (i = 0; i < n; i = i + 2 * width)
		{
			// Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[]
			// or copy A[i:n-1] to B[] ( if(i+width >= n) )
			ft_merge(A, i, min(i+width, n), min(i+2*width, n), B, env);
		}
		// Now work array B is full of runs of length 2*width.
		// Copy array B to array A for next iteration.
		// A more efficient implementation would swap the roles of A and B.
		ft_copy_tab_op(A, B, n, env);
		// Now array A is full of runs of length 2*width.
	}
}

void	ft_do_operate(char *operation, t_env *env, int *state)
{
//	ft_putstr("DO ");
//	ft_putendl(operation);
	ft_operate(operation, env);
	ft_lstaddend(&env->operations, ft_lstnew(operation, ft_strlen(operation)));
	*state = 1;
}

void	ft_sort(t_env *env)
{
	int	sorting;

//	ft_putendl(" === SORTING... === ");
//	ft_display_stacks(*env);

	if (ft_checker_check(*env))
		return ;
	sorting = 0;
	if (env->stack_a_size >= 1 && env->stack_a[env->stack_a_size - 1] > env->stack_a[0])
		ft_do_operate("rra", env, &sorting);
	else if (env->stack_b_size >= 1 && env->stack_b[env->stack_b_size - 1] < env->stack_b[0])
		ft_do_operate("rrb", env, &sorting);
	else if (env->stack_a_size >= 1 && env->stack_a[env->stack_a_size - 1] > env->stack_a[0])
		ft_do_operate("ra", env, &sorting);
	else if (env->stack_b_size >= 1 && env->stack_b[env->stack_b_size - 1] < env->stack_b[0])
		ft_do_operate("rb", env, &sorting);
	else if (env->stack_a_size > 1 && env->stack_a[env->stack_a_size - 1] > env->stack_a[env->stack_a_size - 2])
		ft_do_operate("sa", env, &sorting);
	else if (env->stack_b_size > 1 && env->stack_b[env->stack_b_size - 1] < env->stack_b[env->stack_b_size - 2])
		ft_do_operate("sb", env, &sorting);
	if (!sorting && env->stack_a_size > 1 && env->stack_a[env->stack_a_size - 1] < env->stack_a[env->stack_a_size - 2])
		ft_do_operate("pb", env, &sorting);
	if (sorting)
		ft_sort(env);
	else
	{
		int	i = 0;
		while (i < env->stack_b_size)
			ft_do_operate("pa", env, &sorting);
	}
}

void	ft_push_swap_process(t_env *env)
{
	//t_array	result;

	//result.tab = env->stack_a;
	//result.n = env->stack_a_size - 1;
	//result = ft_merge_sort(result);
	//env->stack_a = result.tab;
	//env->stack_b = malloc(sizeof(int) * env->stack_a_size);
	//ft_merge_sort(env->stack_a, env->stack_b, env->stack_a_size, env);
	//ft_quicksort(env->stack_a, env->stack_a_size);
	ft_sort(env);
//	ft_putendl(" === SORTED === ");
//	ft_display_stacks(*env);
//	ft_putendl(" ==== OPERATIONS ====");
	ft_display_operations(*env); // TODO: Malloc directement stack_b de la taille de stack_a
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
	//free(env.stack_a);
	//free(env.stack_b);
	return (EXIT_SUCCESS);
}
