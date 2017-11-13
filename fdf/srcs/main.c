/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:04:17 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 13:06:20 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int main(int argc, const char *argv[])
{
	if (argc != 2)
		ft_putstr("Usage : ./fdf <filename>\n");
	else
		ft_display(ft_read(argv[1]));
	return 0;
}
