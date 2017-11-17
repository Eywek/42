/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:50:34 by valentin          #+#    #+#             */
/*   Updated: 2017/11/17 21:02:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct      s_modifier
{
    char            letter;
    int             id;
}                   t_modifier;

typedef struct      s_flag
{
    char            *letters;
    int             (*function)(va_list argv, t_modifier modifier);
}                   t_flag;

#endif