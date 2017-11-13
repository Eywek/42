/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:18:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 13:59:53 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

t_list	*ft_read(const char *filename);
void	ft_display(t_list *lines);

#endif
