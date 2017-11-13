/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jechoque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:37:03 by jechoque          #+#    #+#             */
/*   Updated: 2017/11/12 17:59:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include "libft/libft.h"

typedef struct		s_tetri
{
	char			**minos;
	char			letter;
	int				height;
	int				width;
}					t_tetri;

typedef struct		s_size
{
	int				height;
	int				width;
}					t_size;

t_list				*ft_read_fd(int fd);

int					ft_bufcheck(char *buffer, int length);

char				**ft_new_tab(int size);
char				**ft_solve(t_list *tetriminos);

void				ft_display(char **map);
void				ft_throw_error();

#endif
