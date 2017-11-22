/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 14:01:07 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 14:05:56 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"


void	ft_putnbr_fd_unsigned(unsigned int nbr, int fd, int *size)
{
	*size += 1;
	if (nbr >= 10)
		ft_putnbr_fd_unsigned(nbr / 10, fd, size);
	ft_putchar_fd((char)(nbr % 10 + 48), fd);
}
