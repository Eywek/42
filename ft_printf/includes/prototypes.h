/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 17:03:06 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include <stdint.h>
# include <stddef.h>
# include <wchar.h>

int			type_c(va_list args, t_flags *flags);
int			type_s(va_list args, t_flags *flags);
int			type_d(va_list args, t_flags *flags);
int			type_percentage(va_list args, t_flags *flags);
int			type_p(va_list args, t_flags *flags);
int			type_o(va_list args, t_flags *flags);
int			type_x(va_list args, t_flags *flags);
int			type_x_upper(va_list args, t_flags *flags);
int			type_u(va_list args, t_flags *flags);
int			type_s_upper(va_list args, t_flags *flags);
int			type_c_upper(va_list args, t_flags *flags);
int			type_d_upper(va_list args, t_flags *flags);
int			type_o_upper(va_list args, t_flags *flags);
int			type_u_upper(va_list args, t_flags *flags);
int			type_a(va_list args, t_flags *flags);
int			type_a_upper(va_list args, t_flags *flags);
int			type_f(va_list args, t_flags *flags);
int			type_f_upper(va_list args, t_flags *flags);
int			type_b(va_list args, t_flags *flags);
int			type_n(va_list args, t_flags *flags);

void		ft_edit_length_type(char **str, t_flags *flags, int flag_type,
								int size);
void		ft_init_flags(t_flags *flags);
int			ft_handle_flags(char **str, t_flags *flags);
int			ft_handle_width(char **str, t_flags *flags, va_list args);
int			ft_handle_precision(char **str, t_flags *flags, va_list args);
int			ft_handle_length(char **str, t_flags *flags);

int			ft_pad(t_flags *flags, int size);

intmax_t	ft_get_nb(va_list args, t_flags flags);
uintmax_t	ft_get_nb_u(va_list args, t_flags flags);
void		ft_putnbr_base_intmax_t_u(uintmax_t nbr, char *str,
									uintmax_t str_length, t_flags *flags);
void		ft_get_number_size_u(uintmax_t nbr, uintmax_t str_length,
								int *size);
int			ft_pad_nb(va_list args, t_flags *flags, char *base,
						char *hash_key_content);
int			ft_display_d(t_flags *flags, int size, int precision, intmax_t nb);
void		ft_display_sign(intmax_t nb, t_flags *flags);
void		ft_display_padding(t_flags *flags, uintmax_t nb, int *size,
							char *base);
int			ft_get_wchar_size(wint_t c);
int			ft_get_wstr_size(wchar_t *s, int max);
int			ft_put_float_to_string(double nb, char **s, int precision);
int			ft_handle_colors(char **str, int size, t_flags *flags, int max);

int			ft_write_wchar(wint_t c, t_flags *flags);
int			ft_write_char(char c, t_flags *flags);
int			ft_write_until_percentage(char **format, t_flags *flags);
int			ft_write(void *str, int size, t_flags *flags);
int			ft_printf(const char *restrict format, ...);

#endif
