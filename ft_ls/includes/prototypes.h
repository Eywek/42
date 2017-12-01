/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:48:06 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 14:48:43 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

void				ft_usage(void);
void				ft_throw_error_options(char *option);
void				ft_throw_error_memory(void);
void				ft_throw_error_file_not_found(char *filename);

int					ft_is_dir(char *filename);
int					ft_is_file(char *filename);
int					ft_is_file_or_dir(char *filename);

#endif
