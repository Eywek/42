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
	double cRe;
	double cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
	double newRe;
	double newIm;
	double oldRe;
	double oldIm;   //real and imaginary parts of new and old
	double zoom = env->options.zoom;
	double moveX = env->options.x;
	double moveY = env->options.y; //you can change these to zoom and change position
	t_color color; //the RGB color value for the pixel
	int maxIterations = env->options.iterations; //after how much iterations the function should stop

	cRe = -0.7;
	cIm = 0.27015;
	for(int y = 0; y < WIN_HEIGHT; y++)
		for(int x = 0; x < WIN_WIDTH; x++)
		{
			newRe = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * zoom * WIN_WIDTH) + moveX;
			newIm = (y - WIN_HEIGHT / 2) / (0.5 * zoom * WIN_HEIGHT) + moveY;
			int i;
			for(i = 0; i < maxIterations; i++)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + cRe;
				newIm = 2 * oldRe * oldIm + cIm;
				if((newRe * newRe + newIm * newIm) > 4) break;
			}
			color.blue = i % 256;
			color.green = 255;
			color.red = 255 * (i < maxIterations);
			ft_putpixel(env, x, y, color);
		}
}
