/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:32:03 by vtouffet          #+#    #+#             */
/*   Updated: 2018/04/22 13:44:46 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_del_operation(void *name, size_t size)
{
	(void)size;
	free(name);
}

void	ft_checker_order(t_env *env)
{
	t_list	*operations;

	operations = env->operations;
	while (operations)
	{
		ft_operate(operations->content, env);
		operations = operations->next;
	}
}

int		main(int argc, char *argv[])
{
	t_env	env;

	if (argc == 1)
		return (EXIT_SUCCESS);
	if (!(env.stack_a = malloc(sizeof(int))) ||
		!(env.stack_b = malloc(sizeof(int))))
		ft_checker_error();
	ft_memset(&env, 0, sizeof(env));
	ft_checker_handle_stack(argc, argv, 0, &env);
	ft_checker_handle_operations(&env);
	ft_checker_order(&env);
	if (ft_checker_check(env))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	free(env.stack_a);
	free(env.stack_b);
	ft_lstdel(&env.operations, &ft_del_operation);
	return (EXIT_SUCCESS);
}
