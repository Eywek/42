/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:19:03 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/09 14:44:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct			s_shell_env {
	char				*name;
	char				*value;
	struct s_shell_env	*next;
}						t_shell_env;

typedef struct			s_env {
	t_shell_env			*shell_env;
	t_shell_env			*tmp_env;
	int					use_tmp_env;
	int					exit;
	int					exit_code;
	int					is_processing;
}						t_env;

typedef struct			s_builtin {
	char				*name;
	void				(*f)(const char *content);
}						t_builtin;

t_env					g_env;

#endif
