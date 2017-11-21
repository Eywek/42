/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:25:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 18:55:28 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/core.h"

int main(int argc, char *argv[])
{
	char *s = "Coucou";
	printf("Result = %d chars\n", ft_printf("Coucou %5.2s %% ca va ?\nTu as %03d ans\nLol %d c\nPointer: %p\n", "Valentin", 18, 5, &s));
	return (0);
}
