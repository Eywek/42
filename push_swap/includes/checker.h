/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 23:56:59 by valentin          #+#    #+#             */
/*   Updated: 2017/12/07 12:31:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
#define CHECKER_H

# include <stdlib.h>
# include "../libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

typedef struct	s_env {
	int			*stack_a;
	int			*stack_b;
	t_list		*operations;
}				t_env;

void	ft_del_operation(void *name, size_t size);
void	ft_checker_error(void);
int		ft_is_valid_operation(char *str);
void	ft_checker_handle_stack(int argc, char *argv[], t_env *env);
void	ft_checker_handle_operations(t_env *env);

#endif
