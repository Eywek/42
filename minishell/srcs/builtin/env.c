/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:56 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/14 13:05:17 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_display_env(void)
{
	t_shell_env *ptr;

	ptr = g_env.shell_env;
	while (ptr)
	{
		ft_printf("%s=%s\n", ptr->name, ptr->value);
		ptr = ptr->next;
	}
}

static void	ft_dup_env(t_shell_env *src)
{
	t_shell_env	*ptr;

	ptr = src;
	while (ptr)
	{
		ft_set_env(ptr->name, ptr->value, 1);
		ptr = ptr->next;
	}
}

static int	ft_handle_setenv(const char *content)
{
	char		*tmp;
	char		*tmp2;
	char		*space_pos;

	tmp = ft_strdup(content);
	space_pos = ft_strchr(tmp, ' ');
	if (space_pos)
		tmp[space_pos - tmp] = 0;
	tmp2 = ft_strdup(ft_strchr(tmp, '=') + 1);
	tmp[ft_strchr(tmp, '=') - tmp] = 0;
	ft_set_env(tmp, tmp2, g_env.use_tmp_env);
	free(tmp);
	free(tmp2);
	return (1);
}

static int	ft_disable_tmp_env(int disable)
{
	if (g_env.tmp_env)
		ft_free_env(g_env.tmp_env);
	g_env.tmp_env = NULL;
	g_env.use_tmp_env = disable ? 0 : 1;
	return (1);
}

void		ft_env(const char *content)
{
	int			add;

	if (!content || !content[0])
		return (ft_display_env());
	g_env.use_tmp_env = 1;
	ft_dup_env(g_env.shell_env);
	while (content && *content)
		if (*content == ' ')
			++content;
		else if (((add = ft_strncmp(content, "-u", 2) == 0) ||
			ft_strncmp(content, "--unset", 7) == 0) &&
			ft_disable_tmp_env(0))
			return (ft_unsetenv((char*)(content + (add ? 3 : 8))));
		else if (((add = ft_strncmp(content, "-i", 2) == 0) ||
			ft_strncmp(content, "--ignore-environment", 20) == 0) &&
			ft_disable_tmp_env(0))
			content += (add ? 2 : 20);
		else if (ft_strchr(content, '=') && ft_handle_setenv(content))
			content = ft_strchr(content, ' ');
		else if (*content != ' ')
		{
			content[(g_env.exit_code = 0)] == '-' ? ft_display_error(5) :
			ft_parse_input((char*)content);
			return ((void)ft_disable_tmp_env(1));
		}
}
