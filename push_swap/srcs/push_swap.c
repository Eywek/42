/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 19:09:55 by vtouffet          #+#    #+#             */
/*   Updated: 2018/04/22 13:52:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_do_operate(char *operation, t_env *env)
{
	ft_operate(operation, env);
	ft_lstaddend(&env->operations, ft_lstnew(operation, ft_strlen(operation)));
}

void	ft_sort(t_env *env)
{
	// TODO
	ft_do_operate("pa", env);
}

void	ft_push_swap_process(t_env *env)
{
	if (env->verbose)
	{
		ft_putendl(" === BEFORE === ");
		ft_display_stacks(*env);
	}
	if (!ft_checker_check(*env))
		ft_sort(env);
	if (env->verbose)
	{
		ft_putendl(" === SORTED === ");
		ft_display_stacks(*env);
		ft_putendl(" ==== OPERATIONS ====");
	}
	ft_display_operations(*env); // TODO: Malloc directement stack_b de la taille de stack_a
}

int		ft_handle_options(int argc, char *argv[], t_env *env)
{
	int	i;
	int	start;

	i = 1;
	start = i;
	while (i < argc - 1)
	{
		if (argv[i][0] == '-')
		{
			while (*(++argv[i]))
			{
				if (*(argv[i]) == 'v')
					++env->verbose;
				else if (*(argv[i]) == 'c')
					++env->color;
			}
			++start;
		}
		++i;
	}
	return (start);
}

int		main(int argc, char *argv[])
{
	t_env	env;
	int		start;

	if (argc < 2)
		return (EXIT_SUCCESS);
	if (!(env.stack_a = malloc(sizeof(int))) ||
		!(env.stack_b = malloc(sizeof(int))))
		ft_checker_error();
	ft_memset(&env, 0, sizeof(env));
	start = ft_handle_options(argc, argv, &env);
	ft_checker_handle_stack(argc, argv, start, &env);
	ft_replace_as_simple_numbers(&env);
	ft_push_swap_process(&env);
	free(env.stack_a);
	free(env.stack_b);
	return (EXIT_SUCCESS);
}
