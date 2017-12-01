/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:25:30 by vtouffet          #+#    #+#             */
/*   Updated: 2017/12/01 15:18:09 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/ft_ls.h"

static void			ft_put_in_folders_options(char *filename, t_options *params)
{
	int	current_index;

	if (!params->folders)
	{
		if (!(params->folders = malloc(sizeof(char*) * 2)))
			return (ft_throw_error_memory());
		params->folders[0] = 0;
	}
	current_index = 0;
	while (params->folders[current_index])
		current_index++;
	if (!(params->folders[current_index] = malloc(sizeof(char) *
														ft_strlen(filename))))
		return (ft_throw_error_memory());
	ft_strcpy(params->folders[current_index], filename);
	params->folders[current_index + 1] = 0;
}

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
		else if (*options == '-')
			state = 1;
	}
	return (state);
}

static void			ft_add_default_folder(t_options *params)
{
	if (!(params->folders = malloc(sizeof(char*) * 2)) ||
		!(params->folders[0] = malloc(sizeof(char) * 2)))
		return (ft_throw_error_memory());
	params->folders[0] = ".";
	params->folders[1] = 0;
}

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
			ft_put_in_folders_options(argv[count], &params);
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

int					main(int argc, char *argv[])
{
	t_options	params;

	params = ft_handle_params(argc, argv);
	ft_printf("params.hidden_files = %d\n", params.hidden_files);
	ft_printf("params.long_format = %d\n", params.long_format);
	ft_printf("params.recursive = %d\n", params.recursive);
	ft_printf("params.sort_by_time = %d\n", params.sort_by_time);
	ft_printf("params.reverse = %d\n", params.sort_reverse);
	ft_printf("params.folders : \n%A\n", params.folders);
	//ft_display(ft_find_files(params), params);
	return (0);
}
