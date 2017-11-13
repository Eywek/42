/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_wstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:14:05 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/13 18:33:22 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i++]);
	return (i - 1);
}

void	rev_wstr(char *str, int first)
{
	int	start;
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		++i;
	if (!str[i]) return;
	start = i;
	while (str[i] && str[i] != ' ')
		i++;
	rev_wstr(str + i, 0);
	write(1, str + start, i - start);
	if (!first)
		write(1, " ", 1);
}

int		main(int argc, const char *argv[])
{
	if (argc == 2)
		rev_wstr((char*)argv[1], 1);
	ft_putchar('\n');
	return 0;
}
