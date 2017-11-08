/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:06:10 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/07 19:01:19 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char *line;

	line = malloc(4096);
	get_next_line(open("test", O_RDONLY), &line);
	printf("line 1 = %s\n", line);
	line = malloc(4096);
	get_next_line(open("test", O_RDONLY), &line);
	printf("line 2 = %s\n", line);
	line = malloc(4096);
	get_next_line(open("test", O_RDONLY), &line);
	printf("line 3 = %s\n", line);
	return 0;
}
