/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 12:18:22 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 17:21:02 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTOTYPES_H
# define MINISHELL_PROTOTYPES_H

# include "structs.h"

void	ft_display_prompt();
void	ft_display_error(int code);
void	ft_display_error_msg(const char *prefix, const char *suffix);

void	ft_wait_input();
void	ft_parse_input(char *line);
void	ft_handle_env(char **env);

int		ft_set_env(const char *name, const char *value, int tmp);
char	*ft_get_env(const char *name);
void	ft_get_kv(char *line, char **key, char **value);
int		ft_count_env();

void	ft_launch(const char *path, const char *args);
void	ft_execute(const char *cmd, const char *args);
char	**ft_make_env();

char	*ft_pathabs(char const *path, char *res, char *to);

void	ft_free_tab(char **tab);
void	ft_free_env(t_shell_env	*env);
int		ft_is_exec(char *path);
void	ft_free_env_el(t_shell_env *el);

void	ft_cd(const char *content);
void	ft_echo(const char *content);
void	ft_env(const char *content);
void	ft_exit(const char *content);
void	ft_setenv(const char *content);
void	ft_unsetenv(const char *content);

#endif
