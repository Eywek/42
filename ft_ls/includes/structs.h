/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:43:44 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/05 14:18:49 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_options {
	int				hidden_files;
	int				recursive;
	int				long_format;
	int				sort_by_time;
	int				sort_reverse;
	int				no_columns;
	int				options_count;
	int				display_dirs;
	int				dirs_count;
	char			*current_path;
	char			**folders;
	char			**files;
	char			**not_founds;
	int				status;
}					t_options;

typedef struct		s_display {
	int				max_hard_link_len;
	int				max_user_len;
	int				max_group_len;
	int				max_size_len;
	int				max_name_len;
	int				total_blocks;
}					t_display;

typedef struct		s_file {
	char			*name;
	char			*path;
	struct stat		stats;
	struct s_file	*next;
}					t_file;

typedef struct		s_dir {
	char			*name;
	struct stat		stats;
	t_file			*files;
	struct s_dir	*next;
}					t_dir;

#endif
