/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:28:32 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

int		flag_c(va_list args, t_flags flags);
int		flag_s(va_list args, t_flags flags);
int		flag_d(va_list args, t_flags flags);
int		flag_percentage(va_list args, t_flags flags);

int		ft_flag_width(char *str, t_flags *flags);

int		ft_printf(const char * restrict format, ...);

#endif
