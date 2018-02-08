/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:18:22 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/08 15:20:25 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTOTYPES_H
#define MINISHELL_PROTOTYPES_H

void    ft_display_prompt();
void    ft_display_error(int code);

void    ft_wait_input();
void    ft_parse_input(char *line);
void    ft_handle_env(char **env);

int     ft_set_env(const char *name, const char *value);
char    *ft_get_env(const char *name);

void    ft_cd(const char *content);
void    ft_echo(const char *content);
void    ft_env(const char *content);
void    ft_exit(const char *content);
void    ft_setenv(const char *content);
void    ft_unsetenv(const char *content);

#endif
