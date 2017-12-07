/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:25:30 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/07 12:14:13 by vtouffet         ###   ########.fr       */
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
												(ft_strlen(filename) + 1))))
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
		else if (*options == 'G' && (state = 1) == 1)
			params->colors = 1;
		else
			ft_throw_error_options(*options);
	if (state)
		params->options_count++;
	return (state);
}

int					ft_handle_param(char *param, int *errors_count,
		int *check_for_flags, t_options *params)
{
	int	files_count;

	files_count = 0;
	if (param[0] == '-' && param[1] && *check_for_flags)
	{
		if (ft_strcmp(param, "--") == 0 && ++params->options_count)
			*check_for_flags = 0;
		else
			ft_set_options(param, params);
	}
	else if (ft_is_file_or_dir(param))
	{
		ft_put_in_options(param, ft_is_file(param) ?
				&(params->files) : &(params->folders));
		*check_for_flags = 0;
		files_count++;
	}
	else if (ft_strlen(param) == 0)
		ft_throw_error_fts_open();
	else if (++(*errors_count))
		ft_put_in_options(param, &(params->not_founds));
	return (files_count);
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
		files_count += ft_handle_param(argv[count], &errors_count,
				&check_for_flags, &params);
	if (errors_count > 0)
		ft_throw_error_files_not_found(params.not_founds, &params);
	params.display_dirs = argc - params.options_count > 2;
	if (files_count == 0 && errors_count == 0)
		ft_add_default_folder(&params);
	ft_sort_params(&params);
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
	ft_find_files(&params);
	return (params.status);
}
