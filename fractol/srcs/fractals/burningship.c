/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/23 14:49:49 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

double  ft_abs(double nb) {
    return nb < 0 ? -nb : nb;
}

void	ft_burningship(t_env *env)
{
    t_color color;
    double zx;
    double zy;
    double i;
    double r;
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < WIN_WIDTH) {
        while (y < WIN_HEIGHT) {
            r = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * env->options.zoom * WIN_WIDTH) + env->options.x; // zx represents the real part of z
            i = (y - WIN_HEIGHT / 2) / (0.5 * env->options.zoom * WIN_HEIGHT) + env->options.y; // zy represents the imaginary part of z
            zx = 0;
            zy = 0;

            int iteration = 0;
            int max_iteration = 1000;
            while (zx * zx + zy * zy < 4 && iteration < max_iteration) {
                double xtemp = zx * zx - zy * zy + i;
                zy = ft_abs(2 * zx * zy) + r; //abs returns the absolute value
                zx = ft_abs(xtemp);

                iteration = iteration + 1;
            }

            color.blue = iteration % 256;
            color.green = 255;
            color.red = 255 * (iteration < max_iteration);
            ft_putpixel(env, x, y, color);
            y++;
        }
        x++;
    }
}
