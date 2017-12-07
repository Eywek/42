/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 23:56:59 by valentin          #+#    #+#             */
/*   Updated: 2017/12/07 01:21:17 by valentin         ###   ########.fr       */
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

#endif
