/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 23:56:59 by valentin          #+#    #+#             */
/*   Updated: 2017/12/22 15:42:11 by valentin         ###   ########.fr       */
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
	int			stack_a_size;
	int			stack_b_size;
	t_list		*operations;
	int			verbose;
	int			color;
}				t_env;

void	ft_del_operation(void *name, size_t size);
void	ft_checker_error(void);
int		ft_is_valid_operation(char *str);
void	ft_checker_handle_stack(int argc, char *argv[], int start, t_env *env);
void	ft_checker_handle_line(t_env *env, char *line);
void	ft_checker_handle_operations(t_env *env);
void	ft_operate(char *operation, t_env *env);
int		ft_checker_check(t_env env);
int		ft_checker_check_a(t_env env);
void	ft_push_tab(int **tab1, int *size1, int **tab2, int *size2);

void	ft_display_stacks(t_env env);

#endif
