/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/07/01 15:56:36 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void	ft_julia(t_env *env)
{
    t_fractal   fractal;
	t_color     color;
    int         y;
    int         x;

    y = -1;
	while (++y < WIN_HEIGHT) {
        x = -1;
        while (++x < WIN_WIDTH) {
            fractal.nr = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * env->options.zoom * WIN_WIDTH) + env->options.x;
            fractal.ni = (y - WIN_HEIGHT / 2) / (0.5 * env->options.zoom * WIN_HEIGHT) + env->options.y;
            fractal.i = -1;
            while (++(fractal.i) < env->options.iterations) {
                fractal.pr = fractal.nr;
                fractal.pi = fractal.ni;
                fractal.nr = fractal.pr * fractal.pr - fractal.pi * fractal.pi + -0.7;
                fractal.ni = 2 * fractal.pr * fractal.pi + 0.27015;
                if ((fractal.nr * fractal.nr + fractal.ni * fractal.ni) > 4)
                    break;
            }
            color.blue = fractal.i % 256;
            color.green = 255;
            color.red = 255 * (fractal.i < env->options.iterations);
            ft_putpixel(env, x, y, color);
        }
    }
}
