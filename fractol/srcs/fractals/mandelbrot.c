/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:17:33 by vtouffet          #+#    #+#             */
/*   Updated: 2018/07/01 16:53:25 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fractol.h"

void	ft_mandelbrot(t_env *env)
{
	//each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
	double pr, pi;           //real and imaginary part of the pixel p
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
	double zoom = env->options.zoom, moveX = -0.5, moveY = 0; //you can change these to zoom and change position
	t_color color; //the RGB color value for the pixel
	int maxIterations = 300;//after how much iterations the function should stop

	//loop through every pixel
	for(int y = 0; y < WIN_HEIGHT; y++)
		for(int x = 0; x < WIN_WIDTH; x++)
		{
			//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
			pr = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * zoom * WIN_WIDTH) + moveX;
			pi = (y - WIN_HEIGHT / 2) / (0.5 * zoom * WIN_HEIGHT) + moveY;
			newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
			//"i" will represent the number of iterations
			int i;
			//start the iteration process
			for(i = 0; i < maxIterations; i++)
			{
				//remember value of previous iteration
				oldRe = newRe;
				oldIm = newIm;
				//the actual iteration, the real and imaginary part are calculated
				newRe = oldRe * oldRe - oldIm * oldIm + pr;
				newIm = 2 * oldRe * oldIm + pi;
				//if the point is outside the circle with radius 2: stop
				if((newRe * newRe + newIm * newIm) > 4) break;
			}
			//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
			color.blue = i % 256;
			color.green = 255;
			color.red = 255 * (i < maxIterations);
			//draw the pixel
			ft_putpixel(env, x, y, color);
		}
}
