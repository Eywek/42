/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:48:06 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/02 17:42:07 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*
 ** ERRORS
*/

void				ft_usage(void);
void				ft_throw_error_options(char *option);
void				ft_throw_error_memory(void);
void				ft_throw_error_file_not_found(char *filename);
void				ft_throw_failed_open_dir(const char *dirname);

/*
 ** DIRECTORY / FILE
*/

int					ft_is_dir(char *filename);
int					ft_is_file(char *filename);
int					ft_is_file_or_dir(char *filename);

struct stat			ft_get_file_stats(t_file file);
char				*ft_get_user_name(uid_t id);
char				*ft_get_group_name(uid_t id);

char				*ft_set_path(char *path, const char *add);

/*
 ** MEMORY
*/

void				ft_free_tab(char **tab);
void				ft_copy_tab(char ***tab, char **ref);

/*
 ** DEBUG
*/

void				ft_debug_options(t_options params);
void				ft_debug_dirs(t_dir *dirs);

/*
 ** GENERAL
*/

t_dir				*ft_find_files(t_options params);

#endif
