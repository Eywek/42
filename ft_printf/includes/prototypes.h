/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 20:33:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include <stdint.h>
#include <stddef.h>

int			flag_c(va_list args, t_flags flags);
int			flag_s(va_list args, t_flags flags);
int			flag_d(va_list args, t_flags flags);
int			flag_percentage(va_list args, t_flags flags);
int			flag_p(va_list args, t_flags flags);
int			flag_o(va_list args, t_flags flags);
int			flag_x(va_list args, t_flags flags);
int			flag_X(va_list args, t_flags flags);
int			flag_u(va_list args, t_flags flags);
int			flag_S(va_list args, t_flags flags);
int			flag_C(va_list args, t_flags flags);
int			flag_D(va_list args, t_flags flags);
int			flag_O(va_list args, t_flags flags);
int			flag_U(va_list args, t_flags flags);

void		ft_init_flags(t_flags *flags);
int			ft_handle_flags(char **str, t_flags *flags);
void 		ft_handle_width(char **str, t_flags *flags);
void 		ft_handle_precision(char **str, t_flags *flags);
void 		ft_handle_length(char **str, t_flags *flags);

intmax_t	ft_get_nb(va_list args, t_flags flags);
uintmax_t	ft_get_nb_u(va_list args, t_flags flags);
void		ft_putnbr_base_intmax_t(intmax_t nbr, char *str,
									intmax_t str_length);
void		ft_get_number_size(intmax_t nbr, intmax_t str_length, int *size);
void		ft_putnbr_base_intmax_t_u(uintmax_t nbr, char *str,
									uintmax_t str_length);
void		ft_get_number_size_u(uintmax_t nbr, uintmax_t str_length, int *size);
int			ft_pad_nb(va_list args, t_flags flags, char *base,
						 char *hash_key_content);

int			ft_printf(const char * restrict format, ...);

#endif
