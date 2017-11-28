/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:27:01 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/28 14:27:08 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

intmax_t	ft_get_nb(va_list args, t_flags flags)
{
	intmax_t	nbr;

	nbr = va_arg(args, intmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (intmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

uintmax_t	ft_get_nb_u(va_list args, t_flags flags)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (unsigned char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (unsigned short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (unsigned long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (unsigned long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (uintmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}
