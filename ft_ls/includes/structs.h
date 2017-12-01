/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:43:44 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 12:07:25 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_options {
	int			hidden_files;
	int			recursive;
	int			long_format;
	int			sort_by_time;
	int			sort_reverse;
	char		**folders;
}				t_options;

#endif
