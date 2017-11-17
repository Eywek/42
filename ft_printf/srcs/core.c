/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:35:41 by valentin          #+#    #+#             */
/*   Updated: 2017/11/17 20:59:24 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

int ft_handle_percentage(char *str, va_list args)
{
    // check si la precision fait partit des flags gerer + lancer la fonction qui s'occupe de trouver la fonction correspondante
}

int ft_printf(const char * restrict format, ...)
{
    int     bytes;
    va_list args;

    bytes = 0;
    ft_init();
    va_start(args, format);

    // % -> check si y'a un flag et si le format est valide a travers ft_handle_percentage


    va_end(args);
    return (bytes);
}