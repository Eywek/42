/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:50:34 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 18:27:57 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


typedef	struct 	s_flags
{
	int 		hash_key;
	int 		zero;
	int 		minus;
	int 		plus;
	int 		space;
	int 		width;
	int 		precision;
	int 		length_type;
}				t_flags;

typedef struct	s_types
{
	char		name;
	int			(*f)(va_list, t_flags);
}				t_types;

#endif
