/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 19:32:42 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_push_swap_process(t_env *env)
{
	(void)env;
	ft_putstr("Soon...\n");
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
