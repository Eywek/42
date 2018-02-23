/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:19:03 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:49:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_STRUCTS_H
# define FRACTOL_STRUCTS_H

typedef struct	s_fractal
{
	char		*name;
	void		(*f)(void *env);
	double		nr;
	double		pi;
	double		po;
	double		ni;
	double		rp;
	double		i;
}				t_fractal;

typedef struct	s_env
{
	void		*mlx_id;
	void		*mlx_win;
	void		*mlx_img;
	char		*image;
	int			bpp;
	int			endian;
	int			size;
	void		(*fractal)(void *env);
}				t_env;

#endif
