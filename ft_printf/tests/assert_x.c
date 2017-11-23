/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert_x.c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <null>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:33:21 by valentin          #+#    #+#             */
/*   Updated: 2017/11/23 19:40:15 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "../includes/core.h"


int test_x(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%x", 10)) - 1 == (*ft_printf_size = ft_printf("%x", 10)));
}

int test_hx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%hx", (unsigned short)10)) - 1 == (*ft_printf_size = ft_printf("%hx", (unsigned short)10)));
}

int test_hhx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%hhx", (unsigned char)10)) - 1 == (*ft_printf_size = ft_printf("%hhx", (unsigned char)10)));
}

int test_lx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%lx", (unsigned long)10)) - 1 == (*ft_printf_size = ft_printf("%lx", (unsigned long)10)));
}

int test_llx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%llx", (unsigned long long)10)) - 1 == (*ft_printf_size = ft_printf("%llx", (unsigned long long)10)));
}

int test_jx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%jx", (uintmax_t)10)) - 1 == (*ft_printf_size = ft_printf("%jx", (uintmax_t)10)));
}

int test_zx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%zx", (size_t)10)) - 1 == (*ft_printf_size = ft_printf("%zx", (size_t)10)));
}

int test_hash_key_x(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#x", 10)) - 1 == (*ft_printf_size = ft_printf("%#x", 10)));
}

int test_hash_key_hx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#hx", (unsigned short)10)) - 1 == (*ft_printf_size = ft_printf("%#hx", (unsigned short)10)));
}

int test_hash_key_hhx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#hhx", (unsigned char)10)) - 1 == (*ft_printf_size = ft_printf("%#hhx", (unsigned char)10)));
}

int test_hash_key_lx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#lx", (unsigned long)10)) - 1 == (*ft_printf_size = ft_printf("%#lx", (unsigned long)10)));
}

int test_hash_key_llx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#llx", (unsigned long long)10)) - 1 == (*ft_printf_size = ft_printf("%#llx", (unsigned long long)10)));
}

int test_hash_key_jx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#jx", (uintmax_t)10)) - 1 == (*ft_printf_size = ft_printf("%#jx", (uintmax_t)10)));
}

int test_hash_key_zx(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#zx", (size_t)10)) - 1 == (*ft_printf_size = ft_printf("%#zx", (size_t)10)));
}




int test_x_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%x", -10)) - 1 == (*ft_printf_size = ft_printf("%x", -10)));
}

int test_hx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%hx", (unsigned short)-10)) - 1 == (*ft_printf_size = ft_printf("%hx", (unsigned short)-10)));
}

int test_hhx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%hhx", (unsigned char)-10)) - 1 == (*ft_printf_size = ft_printf("%hhx", (unsigned char)-10)));
}

int test_lx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%lx", (unsigned long)-10)) - 1 == (*ft_printf_size = ft_printf("%lx", (unsigned long)-10)));
}

int test_llx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%llx", (unsigned long long)-10)) - 1 == (*ft_printf_size = ft_printf("%llx", (unsigned long long)-10)));
}

int test_jx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%jx", (uintmax_t)-10)) - 1 == (*ft_printf_size = ft_printf("%jx", (uintmax_t)-10)));
}

int test_zx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%zx", (size_t)-10)) - 1 == (*ft_printf_size = ft_printf("%zx", (size_t)-10)));
}

int test_hash_key_x_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#x", -10)) - 1 == (*ft_printf_size = ft_printf("%#x", -10)));
}

int test_hash_key_hx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#hx", (unsigned short)-10)) - 1 == (*ft_printf_size = ft_printf("%#hx", (unsigned short)-10)));
}

int test_hash_key_hhx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#hhx", (unsigned char)-10)) - 1 == (*ft_printf_size = ft_printf("%#hhx", (unsigned char)-10)));
}

int test_hash_key_lx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#lx", (unsigned long)-10)) - 1 == (*ft_printf_size = ft_printf("%#lx", (unsigned long)-10)));
}

int test_hash_key_llx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#llx", (unsigned long long)-10)) - 1 == (*ft_printf_size = ft_printf("%#llx", (unsigned long long)-10)));
}

int test_hash_key_jx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#jx", (uintmax_t)-10)) - 1 == (*ft_printf_size = ft_printf("%#jx", (uintmax_t)-10)));
}

int test_hash_key_zx_minus(int *printf_size, int *ft_printf_size)
{
	return ((*printf_size = printf("\n%#zx", (size_t)-10)) - 1 == (*ft_printf_size = ft_printf("%#zx", (size_t)-10)));
}

static int try(int (*test)(int *, int *), char *name)
{
	write(1, "TEST %", 6);
	write(1, name, strlen(name));
	write(1, ": ", 2);
	int result;
	char* file = "/Users/valentin/Work/42/ft_printf/tests/output";
	/* Connect standard output to given file */
	fflush(stdout);
	int fd1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0)
		return -1;
	int fd2 = dup(STDOUT_FILENO);
	if (fd2 < 0)
		return -1;
	if (dup2(fd1, STDOUT_FILENO) < 0)
		return -1;
	close(fd1);

	/* Write to standard output */
	int printf_size;
	int ft_printf_size;
	result = test(&printf_size, &ft_printf_size);

	/* Reconnect original standard output */
	fflush(stdout);
	if (dup2(fd2, STDOUT_FILENO) < 0)
		return -1;
	close(fd2);

	/* Check content */
	char str_printf[300];
	char ft_printf[300];
	int fd = open(file, O_RDONLY);
	read(fd, str_printf, (size_t)printf_size);
	str_printf[printf_size - 1] = '\0';
	read(fd, ft_printf, 300);
	close(fd);
	if (strcmp(str_printf, ft_printf) != 0)
	{
		write(1, "ERROR (", 7);
		write(1, str_printf, (size_t)printf_size - 1);
		write(1, " != ", 4);
		write(1, ft_printf, (size_t)ft_printf_size);
		write(1, ")\n", 2);
		remove(file);
		return (0);
	}

	/* Check */
	if (result)
		write(1, "OK\n", 3);
	else
	{
		write(1, "ERROR (size: ", 13);
		ft_putnbr_fd(printf_size, 1);
		write(1, " != ", 4);
		ft_putnbr_fd(ft_printf_size, 1);
		write(1, ")\n", 2);
	}
	remove(file);
	return 0;
}

void	launch_tests(void)
{
	try(&test_x, "x   ");
	try(&test_hx, "hx  ");
	try(&test_hhx, "hhx ");
	try(&test_lx, "lx  ");
	try(&test_llx, "llx ");
	try(&test_jx, "jx  ");
	try(&test_zx, "zx  ");

	try(&test_hash_key_x, "#x  ");
	try(&test_hash_key_hx, "#hx ");
	try(&test_hash_key_hhx, "#hhx");
	try(&test_hash_key_lx, "#lx ");
	try(&test_hash_key_llx, "#llx");
	try(&test_hash_key_jx, "#jx ");
	try(&test_hash_key_zx, "#zx ");

	try(&test_x_minus, "x   ");
	try(&test_hx_minus, "hx  ");
	try(&test_hhx_minus, "hhx ");
	try(&test_lx_minus, "lx  ");
	try(&test_llx_minus, "llx ");
	try(&test_jx_minus, "jx  ");
	try(&test_zx_minus, "zx  ");

	try(&test_hash_key_x_minus, "#x  ");
	try(&test_hash_key_hx_minus, "#hx ");
	try(&test_hash_key_hhx_minus, "#hhx");
	try(&test_hash_key_lx_minus, "#lx ");
	try(&test_hash_key_llx_minus, "#llx");
	try(&test_hash_key_jx_minus, "#jx ");
	try(&test_hash_key_zx_minus, "#zx ");
}
