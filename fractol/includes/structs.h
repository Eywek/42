/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:19:03 by vtouffet          #+#    #+#             */
/*   Updated: 2018/07/01 15:58:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_STRUCTS_H
# define FRACTOL_STRUCTS_H

typedef struct	s_options
{
	double		zoom;
	double		x;
	double		y;
	int			iterations;
}				t_options;

typedef struct	s_env
{
	void		*mlx_id;
	void		*mlx_win;
	void		*mlx_img;
	char		*image;
	int			bpp;
	int			endian;
	int			size;
	void		(*fractal)(struct s_env *env);
	t_options	options;
}				t_env;

typedef struct	s_fractal
{
	char		*name;
	void		(*f)(t_env *env);
	double		nr; // new real
	double		pi; // previous imaginary
	double		ni; // new imaginary
	double		pr; // previous real
    double      tr; // tmp real
    double      ti; // tmp imaginary
	int	    	i; // iterations
}				t_fractal;

typedef struct	s_color
{
	int	red;
	int green;
	int blue;
}				t_color;

#endif
