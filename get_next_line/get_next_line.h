/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:00:35 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/09 12:21:15 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_cache
{
	int				fd;
	char			*content;
	struct s_cache	*next;
}				t_cache;

int	get_next_line(const int fd, char **line);

#endif
