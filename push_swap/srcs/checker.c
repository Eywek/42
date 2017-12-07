/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:32:03 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:32:06 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_del_operation(void *name, size_t size)
{
	(void)size;
	free(name);
}

int		main(int argc, char *argv[])
{
	t_env	env;

	if (argc < 2)
		ft_checker_error();
	if (!(env.stack_a = malloc(sizeof(int))) ||
			!(env.stack_b = malloc(sizeof(int))))
		ft_checker_error();
	ft_memset(&env, 0, sizeof(env));
	ft_checker_handle_stack(argc, argv, &env);
	ft_checker_handle_operations(&env);
	ft_free_tab((void*)(&env.stack_b));
	ft_free_tab((void*)(&env.stack_a));
	ft_lstdel(&env.operations, &ft_del_operation);
	return (EXIT_SUCCESS);
}
