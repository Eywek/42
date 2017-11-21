/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:14:28 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/21 19:02:50 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <printf.h> // TODO: remove
#include "../../includes/core.h"

int	flag_p(va_list args, t_flags flags)
{
	char	*address;
	int		pointer;
	int 	size;

	(void)flags;
	pointer = va_arg(args, int);
	size = 6;
	write(STDOUT, "0x7fff", 6);
	address = ft_itoa_base(pointer, "0123456789abcdef");
	while (address[size - 6])
		++size;
	write(STDOUT, address, (size_t)size - 6);
	return (size);
}
