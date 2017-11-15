/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 12:18:12 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/15 16:16:23 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libs/libft/libft.h"
# include "../libs/get_next_line/get_next_line.h"

# define WINDOW_TITLE "FdF"

# define KEYCODE_ESC 53

typedef	struct	s_point
{
	int 		x;
	int 		y;
	int 		h;
	int 		index;
}				t_point;

typedef	struct	s_options
{
	int 		window_size;
	int 		zoom;
}				t_options;

typedef	struct	s_mlx
{
	void 		*mlx_id;
	void		*window_id;
	t_options 	options;
}				t_mlx;

int 	ft_open_file(const char *filename);
t_list	*ft_read(int fd, t_options options);
void	ft_throw_error(void);
int		ft_listen_key(int keycode, void *param);
void	ft_display(t_list *lines, t_options options);

t_list	*ft_debug_points(t_list *point);

#endif
