/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:58:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 15:57:53 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	ft_handle_colors(char **str, int size, t_flags *flags, int max)
{
	char	*start;

	printf("SEARCH COLORS IN '%s'\n", *str);
	if ((start = ft_strnstr(*str, "{eoc}", (size_t)max)) != 0)
	{
		printf("FOUND {eoc} FROM '%s' INTO '%s'\n", start, *str);
		printf("    WRITE %d chars\n", (int)(start - *str));
		ft_write(*str, (int)(start - *str), flags);
		ft_write("\033[0m", 4, flags);
		printf("    GO TO %d chars\n", (int)(start + 5 - *str));
		size -= (int)(start - *str) + 5;
		*str += (start + 5) - *str;
		printf("    NEW STRING '%s' - size to write = %d\n", *str, size);
	}

	if ((start = ft_strnstr(*str, "{cyan}", (size_t)max)) != 0)
	{
		printf("FOUND {cyan} FROM '%s' INTO '%s'\n", start, *str);
		printf("    WRITE %d chars\n", (int)(start - *str));
		ft_write(*str, (int)(start - *str), flags);
		ft_write("\033[0;36m", 7, flags);
		printf("    GO TO %d chars\n", (int)(start + 6 - *str));
		size -= (int)(start - *str) + 6;
		*str += (start + 6) - *str;
		printf("    NEW STRING '%s' - size to write = %d\n", *str, size);
	}

	if ((start = ft_strnstr(*str, "{red}", (size_t)max)) != 0)
	{
		printf("FOUND {red} FROM '%s' INTO '%s'\n", start, *str);
		printf("    WRITE %d chars\n", (int)(start - *str));
		ft_write(*str, (int)(start - *str), flags);
		ft_write("\033[0;31m", 7, flags);
		printf("    GO TO %d chars\n", (int)(start + 5 - *str));
		size -= (int)(start - *str) + 5;
		*str += (start + 5) - *str;
		printf("    NEW STRING '%s' - size to write = %d\n", *str, size);
	}

	return (size);
//	if ((start = ft_strnstr(*str, "{cyan}", max)) != 0)
//	{
//		printf("FOUND {cyan} FROM '%s' INTO '%s'\n", start, *str);
//		ft_write(*str, (int)(start - *str), flags);
//		ft_write("\033[0;36m", 7, flags);
//		*str += (start + 6) - *str;
//	}
}
