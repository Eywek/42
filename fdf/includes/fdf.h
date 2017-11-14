/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:18:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 15:25:18 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

# define WINDOW_TITLE "FdF"

# define KEYCODE_ESC 53

typedef	struct	s_line
{
	char 		**content;
}				t_line;

typedef	struct	s_options
{
	int 		window_size;
}				t_options;

typedef	struct	s_mlx
{
	void 		*mlx_id;
	void		*window_id;
	t_options 	options;
}				t_mlx;

t_list	*ft_read(const char *filename);
void	ft_throw_error(void);
int		ft_listen_key(int keycode, void *param);
void	ft_display(t_list *lines, t_options options);

#endif
