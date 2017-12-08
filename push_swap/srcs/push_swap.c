/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/08 17:49:31 by vtouffet         ###   ########.fr       */
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
void BottomUpMerge(int *A, int iLeft, int iRight, int iEnd, int *B)
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
			i = i + 1;
		} else {
			B[k] = A[j];
			j = j + 1;
		}
	}
}

void	CopyArray(int *B, int *A, int n)
{
	int	i;

	for(i = 0; i < n; i++)
		A[i] = B[i];
}

void	BottomUpMergeSort(int *A, int *B, int n)
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
			BottomUpMerge(A, i, min(i+width, n), min(i+2*width, n), B);
		}
		// Now work array B is full of runs of length 2*width.
		// Copy array B to array A for next iteration.
		// A more efficient implementation would swap the roles of A and B.
		CopyArray(B, A, n);
		// Now array A is full of runs of length 2*width.
	}
}

void	ft_push_swap_process(t_env *env)
{
	//t_array	result;

	//result.tab = env->stack_a;
	//result.n = env->stack_a_size - 1;
	//result = ft_merge_sort(result);
	//env->stack_a = result.tab;
	env->stack_b = malloc(sizeof(int) * env->stack_a_size);
	BottomUpMergeSort(env->stack_a, env->stack_b, env->stack_a_size);
	//ft_quicksort(env->stack_a, env->stack_a_size);
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
	//free(env.stack_a);
	//free(env.stack_b);
	return (EXIT_SUCCESS);
}
