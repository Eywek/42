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
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < WIN_WIDTH) {
        while (y < WIN_HEIGHT) {
            zx = x; // zx represents the real part of z
            zy = y; // zy represents the imaginary part of z


            int iteration = 0;
            int max_iteration = 1000;
            while (zx * zx + zy * zy < 4 && iteration < max_iteration) {
                double xtemp = zx * zx - zy * zy + x;
                zy = ft_abs(2 * zx * zy) + y; //abs returns the absolute value
                zx = ft_abs(xtemp);

                iteration = iteration + 1;
            }

            color.blue = iteration % 256;
            color.green = 255;
            color.red = 255 * (iteration < max_iteration);
            ft_putpixel(env, x++, y++, color);
        }
    }
}
