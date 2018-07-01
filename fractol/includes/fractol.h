/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:05:56 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "structs.h"
# include "prototypes.h"
# include "../libft/libft.h"

# define FRACTALS_COUNT 3
# define FRACTOL_USAGE "usage: fractol [julia, mandelbrot, burningship]\n"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 500
# define WIN_TITLE "Fractol"

# define KEYPRESS 2
# define KEYRELEASE 3
# define MOTIONNOTIFY 6
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASEMASK (1L<<1)
# define POINTERMOTIONMASK (1L<<6)
# define KEY_D 2
# define KEY_C 8
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_T 17
# define KEY_I 34
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53

#endif
