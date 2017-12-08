/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:11:45 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/08 16:11:47 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include "checker.h"

int		ft_quicksort_get_pivot(int *tab, int size);
void 	ft_quicksort(int *tab, int size);
void	ft_push_swap_process(t_env *env);

#endif

