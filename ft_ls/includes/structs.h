/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:43:44 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
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
	int				colors;
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
	int				link_len;
	int				user_len;
	int				group_len;
	int				size_len;
	int				name_len;
	int				total_blocks;
	int				major_len;
	int				minor_len;
	int				c_count;
}					t_display;

typedef struct		s_file {
	char			*name;
	char			*path;
	char			*user;
	char			*group;
	int				major;
	int				minor;
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
