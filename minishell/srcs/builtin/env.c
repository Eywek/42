/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 13:55:56 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/12 19:22:05 by vtouffet         ###   ########.fr       */
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
		ft_set_env(ft_strdup(ptr->name), ft_strdup(ptr->value), 1);
		ptr = ptr->next;
	}
}

void		ft_env(const char *content)
{
	int			add;
	char		*tmp;
	char		*tmp2;

	if (!content || !content[0])
		return (ft_display_env());
	g_env.use_tmp_env = 1;
	ft_dup_env(g_env.shell_env);
	while (content && *content)
	{
		if ((add = ft_strncmp(content, "-u", 2) == 0) ||
			ft_strncmp(content, "--unset", 7) == 0)
		{
			ft_free_env(g_env.tmp_env);
			g_env.use_tmp_env = 0;
			return (ft_unsetenv((char*)(content + (add ? 3 : 8))));
		}
		else if ((add = ft_strncmp(content, "-i", 2) == 0) ||
			ft_strncmp(content, "--ignore-environment", 20) == 0)
		{
			if (g_env.tmp_env)
				ft_free_env(g_env.tmp_env);
			g_env.tmp_env = NULL;
			content += (add ? 2 : 20);
		}
		else if (ft_strchr(content, '='))
		{
			tmp = ft_strdup(content);
			tmp[ft_strchr(tmp, ' ') - tmp] = 0;
			tmp2 = ft_strdup(ft_strchr(tmp, '=') + 1);
			tmp[ft_strchr(tmp, '=') - tmp] = 0;
			ft_printf("ft_set_env('%s', '%s', %d);\n", tmp, tmp2, g_env.use_tmp_env);
			ft_set_env(tmp, tmp2, g_env.use_tmp_env);
			//free(tmp);
			//free(tmp2);
			content = ft_strchr(content, ' ');
		}
		else if (*content != ' ')
		{
			ft_parse_input((char*)content);
			if (g_env.tmp_env)
				ft_free_env(g_env.tmp_env);
			g_env.tmp_env = NULL;
			g_env.use_tmp_env = 0;
			break;
		}
		++content;
	}
}
