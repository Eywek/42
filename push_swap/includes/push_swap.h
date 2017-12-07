/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:11:45 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 19:54:42 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include "checker.h"

int		ft_quicksort_partition(int **tab, int lower, int highter);
void	ft_quicksort(int **tab, int lower, int highter);
void	ft_push_swap_process(t_env *env);

#endif

