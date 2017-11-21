/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:50:34 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 15:38:05 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


typedef	struct 	s_modifiers
{
	int 		hash_key;
	int 		zero;
	int 		minus;
	int 		plus;
	int 		space;
}				t_modifiers;

typedef struct	s_flags
{
	char		*name;
	int			(*f)(va_list, t_modifiers);
}				t_flags;

#endif
