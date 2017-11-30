/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:50:34 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 17:40:13 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdarg.h>
# define BUFF_SIZE 1024

typedef struct	s_flags
{
	int			hash_key;
	int			zero;
	int			minus;
	int			plus;
	int			space;
	int			width;
	int			precision;
	int			length_type;
	char		type;
	char		buffer[BUFF_SIZE];
	int			bytes;
	int			total_bytes;
}				t_flags;

typedef struct	s_types
{
	char		name;
	int			(*f)();
}				t_types;

typedef struct	s_color
{
	char		*name;
	char		*format;
}				t_color;

#endif
