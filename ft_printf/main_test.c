/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:25:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 16:57:20 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/core.h"

int main(int argc, char *argv[])
{
	printf("Result = %d chars\n", ft_printf("Coucou %-10s %% ca va ?\nTu as %+d ans\n", "Valentin", 18));
	return (0);
}
