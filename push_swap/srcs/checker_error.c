/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:30:09 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 17:12:36 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "../includes/checker.h"

void	ft_checker_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int		ft_is_valid_operation(char *str)
{
	if (ft_strcmp(str, "sa") == 0)
		return (1);
	else if (ft_strcmp(str, "sb") == 0)
		return (1);
	else if (ft_strcmp(str, "ss") == 0)
		return (1);
	else if (ft_strcmp(str, "pa") == 0)
		return (1);
	else if (ft_strcmp(str, "pb") == 0)
		return (1);
	else if (ft_strcmp(str, "ra") == 0)
		return (1);
	else if (ft_strcmp(str, "rb") == 0)
		return (1);
	else if (ft_strcmp(str, "rr") == 0)
		return (1);
	else if (ft_strcmp(str, "rra") == 0)
		return (1);
	else if (ft_strcmp(str, "rrb") == 0)
		return (1);
	else if (ft_strcmp(str, "rrr") == 0)
		return (1);
	return (0);
}

void	ft_checker_handle_stack(int argc, char *argv[], t_env *env)
{
	int		count;
	int		nb;
	int		*tmp;

	count = 0;
	(void)argv;
	while (++count < argc)
	{
		if ((nb = ft_getnbr(argv[count])) == 0 &&
				ft_strcmp(argv[count], "0") != 0)
			ft_checker_error();
		if (ft_in_tab(nb, env->stack_a, env->stack_a_size))
			ft_checker_error();
		if (!(tmp = malloc(sizeof(int) * (env->stack_a_size + 1))))
			ft_checker_error();
		ft_copy_tab(tmp, env->stack_a, env->stack_a_size);
		tmp[env->stack_a_size] = nb; // TODO: Free old tab ? lol
		env->stack_a = tmp;
		env->stack_a_size++;
	}
	ft_reverse_tab(&env->stack_a, env->stack_a_size);
}

void	ft_checker_handle_operations(t_env *env)
{
	char	*line;

	env->operations = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_is_valid_operation(line))
			return (ft_checker_error());
		if (ft_strcmp(line, "ss") == 0)
		{
			ft_lstaddend(&env->operations, ft_lstnew("sa", 2));
			ft_lstaddend(&env->operations, ft_lstnew("sb", 2));
		}
		else if (ft_strcmp(line, "rr") == 0)
		{
			ft_lstaddend(&env->operations, ft_lstnew("ra", 2));
			ft_lstaddend(&env->operations, ft_lstnew("rb", 2));
		}
		else if (ft_strcmp(line, "rrr") == 0)
		{
			ft_lstaddend(&env->operations, ft_lstnew("rra", 3));
			ft_lstaddend(&env->operations, ft_lstnew("rrb", 3));
		}
		else
			ft_lstaddend(&env->operations, ft_lstnew(line, ft_strlen(line)));
	}
	free(line);
}
