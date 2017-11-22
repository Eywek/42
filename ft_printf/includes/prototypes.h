/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/22 16:20:33 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include <stdint.h>
#include <stddef.h>

int		flag_c(va_list args, t_flags flags);
int		flag_s(va_list args, t_flags flags);
int		flag_d(va_list args, t_flags flags);
int		flag_percentage(va_list args, t_flags flags);
int		flag_p(va_list args, t_flags flags);
int		flag_o(va_list args, t_flags flags);
int		flag_x(va_list args, t_flags flags);
int		flag_X(va_list args, t_flags flags);
int		flag_u(va_list args, t_flags flags);
int		flag_S(va_list args, t_flags flags);
int		flag_C(va_list args, t_flags flags);
int		flag_D(va_list args, t_flags flags);
int		flag_O(va_list args, t_flags flags);
int		flag_U(va_list args, t_flags flags);

void	ft_init_flags(t_flags *flags);
void	ft_handle_flags(char **str, t_flags *flags);
void 	ft_handle_width(char **str, t_flags *flags);
void 	ft_handle_precision(char **str, t_flags *flags);
void 	ft_handle_length(char **str, t_flags *flags);

void	ft_putnbr_base_unsigned(unsigned int nbr, char *str,
								unsigned int str_length, int *size);
void	ft_putnbr_base_unsigned_long(unsigned long int nbr, char *str,
									 unsigned long int str_length, int *size);
void	ft_putnbr_fd_unsigned(unsigned int nbr, int fd, int *size);
void	ft_putnbr_base_unsigned_long_long(unsigned long long int nbr, char *str,
								  unsigned long long int str_length, int *size);
void	ft_putnbr_base_short_int(short int nbr, char *str,
								 short int str_length, int *size);
void	ft_putnbr_base_uintmax_t(uintmax_t nbr, char *str,
								uintmax_t str_length, int *size);
void	ft_putnbr_base_unsigned_char(unsigned char nbr, char *str,
									 unsigned char str_length, int *size);
void	ft_putnbr_base_size_t(size_t nbr, char *str,
							  size_t str_length, int *size);

int		ft_printf(const char * restrict format, ...);

#endif
