/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 13:19:12 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

int		flag_c(va_list args, int flag);
int		flag_s(va_list args, int flag);
int		flag_d(va_list args, int flag);
int		flag_percentage(va_list args, int flag);

int		ft_printf(const char * restrict format, ...);

#endif
