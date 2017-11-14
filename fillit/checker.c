/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:59:15 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/14 13:29:03 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_checkblock(char *buffer, int i)
{
	int	contact;

	contact = 0;
	if (i <= 14 && buffer[i + 5] == '#')
		contact++;
	if (i >= 4 && buffer[i - 5] == '#')
		contact++;
	if (i >= 1 && buffer[i - 1] == '#')
		contact++;
	if (i <= 19 && buffer[i + 1] == '#')
		contact++;
	if (contact != 1 && contact != 2 && contact != 3)
		return (-56);
	return (contact);
}

int	ft_count_points(char *str)
{
	int	points;

	points = 0;
	while (*str)
	{
		if (*str == '.')
			++points;
		str++;
	}
	return (points == 12);
}

int	ft_bufcheck(char *buf, int buflen)
{
	int	newline;
	int	fullcontact;
	int	i;

	newline = 0;
	fullcontact = 0;
	i = 0;
	while (i < buflen)
	{
		if (((i + 1) % 5 != 0 && buf[i] == '\n')
				|| ((i + 1) % 5 == 0 && (buf[i] != '#' || buf[i] != '.')))
			return (-1);
		if (buf[i] == '#')
			fullcontact += ft_checkblock(buf, i);
		i++;
		while (buf[i] == '\n' && i < buflen)
		{
			i++;
			newline++;
		}
	}
	if (!ft_count_points(buf) || (fullcontact != 6 && fullcontact != 8))
		return (-1);
	return (newline == 4 ? 0 : 1);
}
