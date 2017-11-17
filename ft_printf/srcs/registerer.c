/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registerer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 21:06:12 by valentin          #+#    #+#             */
/*   Updated: 2017/11/17 21:09:32 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

static void ft_init_flags(void)
{
    t_flag c;

    c.function = &ft_print_char;
    c.letters = "c";
}

static void ft_init_modifiers(void)
{

}

void        ft_init(void)
{
    ft_init_flags();
    ft_init_modifiers();
}