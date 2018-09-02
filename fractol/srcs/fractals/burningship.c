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
    t_color     color;
    t_fractal   fractal;
//    double zx;
//    double zy;
//    double i; // iteration
//    double r;
    int x;
    int y;

    y = -1;
    while (++y < WIN_HEIGHT) {
        x = -1;
        while (++x < WIN_WIDTH) {
//            r = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * env->options.zoom * WIN_WIDTH) + env->options.x; // zx represents the real part of z
//            i = (y - WIN_HEIGHT / 2) / (0.5 * env->options.zoom * WIN_HEIGHT) + env->options.y; // zy represents the imaginary part of z
//            zx = 0;
//            zy = 0;
//
//            int iteration = 0;
//            int max_iteration = 1000;
//            while (zx * zx + zy * zy < 4 && iteration < max_iteration) {
//                double xtemp = zx * zx - zy * zy + i;
//                zy = ft_abs(2 * zx * zy) + r; //abs returns the absolute value
//                zx = ft_abs(xtemp);
//
//                iteration = iteration + 1;
//            }
//
//            color.blue = iteration % 256;
//            color.green = 255;
//            color.red = 255 * (iteration < max_iteration);
//            ft_putpixel(env, x, y, color);

            fractal.pr = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * env->options.zoom * WIN_WIDTH) +
                    env->options.x;
            fractal.pi = (x - WIN_HEIGHT / 2) / (0.5 * env->options.zoom * WIN_HEIGHT)
                               + env->options.y;
            fractal.nr = 0;
            fractal.ni = 0;
            double max_iterations = 1000;
            while (++fractal.i < max_iterations && (fractal.nr * fractal.nr +
                                                fractal.ni * fractal.ni) <= 4)
            {
                fractal.tr = fractal.nr;
                fractal.ti = fractal.ni;
                fractal.nr = ft_abs(fractal.tr * fractal.tr - fractal.ti *
                                                           fractal.ti + fractal.pr);
                fractal.ni = ft_abs(2 * fractal.tr * fractal.ti + fractal.pi);
            }
            color.blue = fractal.i % 256;
            color.green = 255;
            color.red = 255 * (fractal.i < max_iterations);
            ft_putpixel(env, x, y, color);
        }
    }
}

//For each pixel (x, y) on the screen, do:
//{
//x = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
//y = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
//
//
//zx = x; // zx represents the real part of z
//zy = y; // zy represents the imaginary part of z
//
//
//iteration = 0
//max_iteration = 1000
//
//while (zx*zx + zy*zy < 4  AND  iteration < max_iteration)
//{
//xtemp = zx*zx - zy*zy + x
//zy = abs(2*zx*zy) + y //abs returns the absolute value
//zx = abs(xtemp)
//
//iteration = iteration + 1
//}
//
//if (iteration == max_iteration) //Belongs to the set
//return insideColor;
//
//return iteration * color;
//}