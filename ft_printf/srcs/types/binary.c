/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:02:27 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 17:03:26 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int	type_b(va_list args, t_flags *flags)
{
	int			size;
	int			nb_size;
	uintmax_t	nb;

	if (flags->precision != 0)
		flags->zero = 0;
	size = 0;
	nb = ft_get_nb_u(args, *flags);
	if (flags->precision >= 0 || nb > 0)
		ft_get_number_size_u(nb, 2, &size);
	if (flags->hash_key && (nb > 0 || flags->precision < 0))
		size += 1;
	nb_size = size;
	size = (flags->precision > size) ? flags->precision : size;
	if (flags->width && !flags->minus)
		size = ft_pad(flags, size);
	if (flags->hash_key && (nb > 0 || flags->precision < 0))
		ft_write("0", 1, flags);
	while (nb_size++ < flags->precision)
		ft_write("0", 1, flags);
	if (flags->precision >= 0 || nb > 0)
		ft_putnbr_base_intmax_t_u(nb, "01", 2, flags);
	if (flags->width && flags->minus)
		size = ft_pad(flags, size);
	return (size);
}
