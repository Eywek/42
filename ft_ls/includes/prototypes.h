/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:48:06 by vtouffet          #+#    #+#             */
/*   Updated: 2018/01/29 12:35:54 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

/*
 ** ERRORS
*/

void				ft_usage(void);
void				ft_throw_error_options(char option);
void				ft_throw_error_memory(void);
void				ft_throw_error_files_not_found(char **files,
						t_options *params);
void				ft_throw_failed_open_dir(const char *dirname,
						t_options *params);
void				ft_throw_error_fts_open(void);

/*
 ** DIRECTORY / FILE
*/

int					ft_is_dir(char *filename);
int					ft_can_browse(t_file file);
int					ft_is_file(char *filename);
int					ft_is_file_or_dir(char *filename);

struct stat			ft_get_file_stats(t_file file);
char				*ft_get_user_name(uid_t id);
char				*ft_get_group_name(uid_t id);
char				ft_get_file_acl(t_file file);

char				*ft_get_link_path(char *path);
char				*ft_set_path(char *path, const char *add);

/*
 ** STATS
*/

struct stat			ft_get_stats_from_name(char *name);

/*
 ** SORTING
*/

void				ft_sort_tab_by_time(char **tab);
void				ft_sort_params(t_options *params);
void				ft_sort_files(t_file **files, int (*f)(t_file *file1,
						t_file *file2));
void				ft_sort_files_reverse(t_file **files);

int					ft_compare_files_mtime(t_file *file1, t_file *file2);
int					ft_compare_files_alpha(t_file *file1, t_file *file2);

/*
 ** MEMORY
*/

void				ft_free_tab(char **tab);
void				ft_copy_tab(char ***tab, char **ref);
void				ft_remove_dir(t_dir **dir);
void				ft_remove_files(t_file **files_list);

/*
 ** MERGE / ADD
*/

void				ft_add_default_folder(t_options *params);
t_dir				*ft_add_folder(const char *name);
void				ft_add_file(t_file **files, char *filename,
						char *current_path);

/*
 ** DEBUG
*/

void				ft_debug_options(t_options params);
void				ft_debug_file(t_file *file);
void				ft_debug_files(t_file *files);
void				ft_debug_dir(t_dir *dir);
void				ft_debug_dirs(t_dir *dirs);

/*
 ** DISPLAY
*/

char				ft_file_type(mode_t mode);
void				ft_display_format_time(time_t date);
void				ft_display_file(t_file *file, t_options params,
						t_display *datas);
void				ft_display_files(t_file *files, t_options params);
void				ft_display_dir(t_dir *dir, t_options params);
void				ft_display_long_file(t_file *file, t_options params,
						t_display datas);
int					ft_get_window_width(void);
void				ft_display_columns(t_file *file, t_options params,
						t_display *datas);
void				ft_display_name(char *format, int width,
							t_file file, t_options params);

/*
 ** GENERAL
*/

void				ft_handle_folder(char *path, t_options *params);
void				ft_find_files(t_options *params);

#endif
