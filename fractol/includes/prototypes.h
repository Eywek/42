/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:18:22 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:36:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_PROTOTYPES_H
# define FRACTOL_PROTOTYPES_H

# include "structs.h"

int		ft_handle_fractal(char *fractal);

void	ft_burningship(t_env *env);
void	ft_mandelbrot(t_env *env);
void	ft_julia(t_env *env);

void	ft_init(t_fractal fractal);
void	ft_draw(t_env *env);
void	ft_putpixel(t_env *env, int x, int y, t_color color);

int	ft_event_key_release(int keycode, t_env *env);
int	ft_event_key_press(int keycode, t_env *env);
int	ft_event_motion(int x, int y, t_env *env);

#endif
