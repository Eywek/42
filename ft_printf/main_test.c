/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:25:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 11:27:34 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "includes/core.h"

int main(int argc, char *argv[])
{
	char *s = "Coucou";
	printf("Result = %d chars\n", ft_printf("Coucou %5.2s %% ca va ?\nTu as %03d ans\nLol %d c\nPointer: %p\n", "Valentin", 18, 5, &s));
	printf("------ %%o ------\n");
	printf("printf: %o\n", 10);
	ft_printf("ft_printf: %o\n", 10);
	printf("printf: %o\n", -10);
	ft_printf("ft_printf: %o\n", -10);
	printf("------- %%x -----\n");
	printf("printf: %x\n", 10);
	ft_printf("ft_printf: %x\n", 10);
	printf("printf: %x\n", -10);
	ft_printf("ft_printf: %x\n", -10);
	printf("------- %%X -----\n");
	printf("printf: %X\n", 10);
	ft_printf("ft_printf: %X\n", 10);
	printf("printf: %X\n", -10);
	ft_printf("ft_printf: %X\n", -10);
	printf("------- %%u -----\n");
	printf("printf: %u\n", 10);
	ft_printf("ft_printf: %u\n", 10);
	printf("printf: %u\n", -10);
	ft_printf("ft_printf: %u\n", -10);
	printf("------- %%-s -----\n");
	printf("printf: %s %-8s %s\n", "coucou", "ca", "va");
	ft_printf("ft_printf: %s %-8s %s\n", "coucou", "ca", "va");
	return (0);
}
