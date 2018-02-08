/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:19:03 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 14:52:01 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
#define MINISHELL_STRUCTS_H

typedef struct s_env {
    char        **shell_env;
}               t_env;

typedef struct s_builtin {
    char        *name;
    void        (*f)(const char *content);
}               t_builtin;

t_env   g_env;

#endif
