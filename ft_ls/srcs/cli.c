/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:25:30 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/03 14:24:15 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

/*
 ** Add file or folder to tab[] for t_options struct
*/

static void			ft_put_in_options(char *filename, char ***old)
{
	char	**tab;
	int		current_index;

	current_index = 0;
	if (*old)
		while ((*old)[current_index])
			current_index++;
	if (!(tab = malloc(sizeof(char*) * (current_index + 2))))
		return (ft_throw_error_memory());
	ft_copy_tab(&tab, *old);
	if (!((tab)[current_index] = malloc(sizeof(char) *
														ft_strlen(filename))))
		return (ft_throw_error_memory());
	ft_strcpy((tab)[current_index], filename);
	(tab)[current_index + 1] = 0;
	*old = tab;
}

/*
 ** Set options in t_options struct with the following option
*/

static int			ft_set_options(char *options, t_options *params)
{
	int	state;

	state = 0;
	while (*(++options))
	{
		if (*options == 'a' && (state = 1) == 1)
			params->hidden_files = 1;
		else if (*options == 'l' && (state = 1) == 1)
			params->long_format = 1;
		else if (*options == 'R' && (state = 1) == 1)
			params->recursive = 1;
		else if (*options == 't' && (state = 1) == 1)
			params->sort_by_time = 1;
		else if (*options == 'r' && (state = 1) == 1)
			params->sort_reverse = 1;
		else if (*options == '1' && (state = 1) == 1)
			params->no_columns = 1;
		else if (*options == '-')
			state = 1;
	}
	return (state);
}

/*
 ** Add the default folder with current path
*/

static void			ft_add_default_folder(t_options *params)
{
	if (!(params->folders = malloc(sizeof(char*) * 2)) ||
		!(params->folders[0] = malloc(sizeof(char) * 2)))
		return (ft_throw_error_memory());
	params->folders[0] = ".";
	params->folders[1] = 0;
}

/*
 ** Parse params with argv, fill the t_options struct with options and
 ** files and folders.
*/

static t_options	ft_handle_params(int argc, char *argv[])
{
	int			count;
	t_options	params;
	int			check_for_flags;
	int			files_count;
	int			errors_count;

	ft_memset(&params, 0, sizeof(params));
	count = 0;
	check_for_flags = 1;
	files_count = 0;
	errors_count = 0;
	while (++count < argc)
	{
		if (ft_is_file_or_dir(argv[count]))
		{
			ft_put_in_options(argv[count], ft_is_file(argv[count]) ? &(params.files) : &(params.folders));
			check_for_flags = 0;
			files_count++;
		}
		else if (argv[count][0] == '-' && argv[count][1] && check_for_flags)
		{
			if (!ft_set_options(argv[count], &params))
				ft_throw_error_options(argv[count]);
			if (ft_strcmp(argv[count], "--") == 0)
				check_for_flags = 0;
		}
		else if (++errors_count)
			ft_throw_error_file_not_found(argv[count]);
	}
	if (files_count == 0 && errors_count == 0)
		ft_add_default_folder(&params);
	return (params);
}

/*
 ** Launch params parsing
 ** Then, start find files
*/

int					main(int argc, char *argv[])
{
	t_options	params;

	params = ft_handle_params(argc, argv);
	ft_debug_options(params);
	ft_debug_dirs(ft_find_files(params));
	return (0);
}
