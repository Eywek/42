/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:35:18 by vtouffet          #+#    #+#             */
/*   Updated: 2018/02/13 15:35:24 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <limits.h>
#include "../includes/minishell.h"

#define PM PATH_MAX

static void		pth_prev(char *res, size_t *len, char **t)
{
	if (*len <= 1)
		return ;
	res[*len - 1] = '\0';
	t[2] = ft_strrchr(res, '/') + 1;
	*t[2] = '\0';
	*len = t[2] - res;
}

static ssize_t	pth_resolve(char *res, size_t rem, size_t len, char *l)
{
	char		*t[3];
	struct stat	sb;
	char		next[PATH_MAX];

	while (rem != 0)
	{
		t[1] = ft_strchr(l, '/');
		t[0] = t[1] ? t[1] : l + rem;
		if (t[0] - l >= (ssize_t)sizeof(next))
			return (-1);
		((char *)ft_memcpy(next, l, t[0] - l))[t[0] - l] = '\0';
		rem -= t[0] - l;
		(t[1] != NULL) ? ft_memmove(l, t[0] + 1, rem + 1) : 0;
		if (res[len - 1] != '/')
			ft_strcpy(res + len++, "/");
		if (!*next && (lstat(res, &sb) != 0 || !S_ISDIR(sb.st_mode)))
			return (-1);
		else if (!*next || ft_strcmp(next, ".") == 0)
			continue ;
		else if (ft_strcmp(next, "..") == 0)
			pth_prev(res, &len, t);
		else if ((len = ft_strlcat(res, next, PM)) >= PM || stat(res, &sb) != 0)
			return (-1);
	}
	return (len);
}

char			*ft_pathabs(char const *path, char *res, char *to)
{
	size_t	rem;
	size_t	len;
	ssize_t	ret;
	char	left[PATH_MAX];

	if (path[0] == '/' && path[1] == '\0')
		return (ft_strcpy(res, path));
	else if (path[0] == '/' && ft_strcpy(res, "/"))
	{
		len = 1;
		rem = ft_strlcpy(left, path + 1, sizeof(left));
	}
	else if (to ? !ft_strcpy(res, to) : !getcwd(res, PATH_MAX))
		return (NULL);
	else
	{
		len = ft_strlen(res);
		rem = ft_strlcpy(left, path, sizeof(left));
	}
	if (rem >= sizeof(left) || len >= PATH_MAX ||
		(ret = pth_resolve(res, rem, len, left)) < 0)
		return (NULL);
	if (ret > 1 && res[ret - 1] == '/')
		res[ret - 1] = '\0';
	return (res);
}
