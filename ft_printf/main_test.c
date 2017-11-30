/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:25:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 16:45:37 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "includes/core.h"
#include "tests/functions.h"
#include <limits.h>
#include <ntsid.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

void	speed(void)
{
	int size;
	int i = 2147483647;
	long l = 2147483647;
	long long ll = 9223372036854775807;
	char c = 0;
	intmax_t im = 9223372036854775807;

	struct timeval stop, start;
	gettimeofday(&start, NULL);
	size = ft_printf("\n");
	size += ft_printf("%%\n");
	//size += ft_printf("%d\n", 42);
	//size += ft_printf("%d%d\n", 42, 41);
	//size += ft_printf("%d%d%d\n", 42, 43, 44);
	//size += ft_printf("%ld\n", l);
	//size += ft_printf("%lld\n", ll);
	//size += ft_printf("%x %X %p %20.15d\n", 505, 505, &ll, 54321); <-- HERE
	//size += ft_printf("%-10d % d %+d %010d %hhd\n", 3, 3, 3, 1, c); <-- HERE
	//size += ft_printf("%jd %zd %u %o %#08x\n", im, (size_t)i, i, 40, 42); <-- HERE
//	size += ft_printf("%x %#X %S %s%s\n", 1000, 1000, L"ݗݜशব", "test", "test2");
	//size += ft_printf("%s%s%s\n", "test", "test", "test");
//	size += ft_printf("%C\n", 15000);
	gettimeofday(&stop, NULL);
	printf("size     = %d in %lu microseconds\n", size, stop.tv_usec - start.tv_usec);
}

void	speed_cmp(void)
{
	int size;
	int i = 2147483647;
	long l = 2147483647;
	long long ll = 9223372036854775807;
	char c = 0;
	intmax_t im = 9223372036854775807;

	struct timeval stop, start;
	gettimeofday(&start, NULL);
	size = printf("\n");
	size += printf("%%\n");
	size += printf("%d\n", 42);
	size += printf("%d%d\n", 42, 41);
	size += printf("%d%d%d\n", 42, 43, 44);
	//size += printf("%ld\n", l);
	//size += printf("%lld\n", ll);
	//size += printf("%x %X %p %20.15d\n", 505, 505, &ll, 54321);
	//size += printf("%-10d % d %+d %010d %hhd\n", 3, 3, 3, 1, c);
	//size += printf("%jd %zd %u %o %#08x\n", im, (size_t)i, i, 40, 42);
//	size += printf("%x %#X %S %s%s\n", 1000, 1000, L"ݗݜशব", "test", "test2");
	size += printf("%s%s%s\n", "test", "test", "test");
//	size += printf("%C\n", 15000);
	gettimeofday(&stop, NULL);
	printf("size cmp = %d in %lu microseconds\n", size, stop.tv_usec - start.tv_usec);
}

int		main(int argc, char *argv[])
{
	//printf("Le fichier {cyan}%s{eoc} contient : {red}%s{eoc}\n", "yolo.txt", "'contenu'");
	//ft_printf("Le fichier {cyan}%s{eoc} contient : {red}%s{eoc}", "yolo.txt", "'contenu'");
	ft_printf("{blue}[{cyan}IMPORTANT{blue}] {eoc}Voici un message {red}important{eoc}, en voici la raison '{yellow}test{eoc}'");
	//ft_printf("{green}[{red}IMPORTANT");
//	speed();
//	speed_cmp();
	//ft_printf("%llu\n", ULLONG_MAX);

//	launch_tests();
//	return (0);

	//char *s = "Coucou";
	//printf("Result = %d chars\n", ft_printf("Coucoy %5.2s %-2% ca va ?\nTu as %03d ans\nLol %d c\nPointer: %p\n", "Valentin", 18, 5, &s));

		//int size = ft_printf("%C", L'米');
//		int size = ft_printf("{%f}", 1444565444646.6465424242242); // 8.49 - 12.10
//		printf("\nsize = %d\n\n", size);
//		size = printf("{%f}", 1444565444646.6465424242242);
//		printf("\nsize = %d\n\n--\n\n", size);
//
//		size = ft_printf("{%f}", INFINITY);
//		printf("\nsize = %d\n\n", size);
//		size = printf("{%f}", INFINITY);
//		printf("\nsize = %d\n", size);

//	int size = ft_printf("{%30S}", L"我"); // 是一只猫。
//	printf("\nsize = %d\n\n", size);

//
//
//
//
//
//
//
//
//
//
//
//
//		ft_printf("%%\n");
//		ft_printf("%d\n", 42);
//		ft_printf("%d%d\n", 42, 41);
//		ft_printf("%d%d%d\n", 42, 43, 44);
//		ft_printf("%ld\n", 2147483647);
//		ft_printf("%lld\n", 9223372036854775807);
//		ft_printf("%x\n", 505);
//		ft_printf("%X\n", 505);
//		ft_printf("%p\n", &ft_printf);
//		ft_printf("%20.15d\n", 54321);
//		ft_printf("%-10d\n", 3);
//		ft_printf("% d\n", 3);
//		ft_printf("%+d\n", 3);
//		ft_printf("%010d\n", 1);
//		ft_printf("%hhd\n", 0);
//		ft_printf("%jd\n", 9223372036854775807);
//		ft_printf("%zd\n", 4294967295);
//		ft_printf("%\n");
//		ft_printf("%U\n", 4294967295);
//		ft_printf("%u\n", 4294967295);
//		ft_printf("%o\n", 40);
//		ft_printf("%%#08x\n", 42);
//		ft_printf("%x\n", 1000);
//		ft_printf("%#X\n", 1000);
//		ft_printf("%s\n", NULL);
//		ft_printf("%S\n", L"ݗݜशব");
//		ft_printf("%s%s\n", "test", "test");
//		ft_printf("%s%s%s\n", "test", "test", "test");
//		ft_printf("%C\n", 15000);
//
//	size = ft_printf("%5d", -42);
//	printf("size = %d\n", size);
//
//	printf("\nsize= %d\n", printf("---printf: %lc\n", L'Á±≥'));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %C\n", L'Á±≥'));
//
//	printf("\nsize= %d\n", printf("---printf: %####0000 33.#00d\n", 256));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %####0000 33.#00d\n", 256));
//
//	printf("\nsize= %d\n", printf("---printf: %####0000 33.0#00d\n", 256));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %####0000 33.0#00d\n", 256));
//
//	printf("\nsize= %d\n", printf("---printf: %####0000 33.#00x\n", 256));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %####0000 33.#00x\n", 256));
//
//	printf("\nsize= %d\n", printf("---printf: %####0000 33.#00o\n", 256));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %####0000 33.#00o\n", 256));
//
//	printf("\nsize= %d\n", printf("---printf: {%05.*d}\n", -15, 42));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: {%05.*d}\n", -15, 42));
//
//	printf("\nsize= %d\n", printf("---printf: %S\n", L"Á±≥"));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %S\n", L"Á±≥"));
//
//	printf("\nsize= %d\n", printf("---printf: %C\n", L'Á'));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %C\n", L'Á'));
//
//	printf("\nsize= %d\n", printf("---printf: %04d\n", -10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %04d\n", -10));
//
//	printf("\nsize= %d\n", printf("---printf: %4d\n", -10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %4d\n", -10));
//
//	printf("\nsize= %d\n", printf("---printf: %5.d %5.0d\n", 0, 0));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %5.d %5.0d\n", 0, 0));
//
//	printf("\nsize= %d\n", printf("---printf: %+ d\n", 42));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %+ d\n", 42));
//
//	printf("\nsize= %d\n", printf("printf: %x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.3x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %.3x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %3x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %3x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %4.3x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %4.3x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %-4.3x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %-4.3x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %4.2x\n", 10));
//	printf("\nsize= %d\n---\n", ft_printf("ft_printf: %4.2x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %4.0x\n", 10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %4.0x\n", 10) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.p\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %.p\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.p\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %.p\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %9.2p\n", 1234));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %9.2p\n", 1234) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.5p\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %.5p\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.5lx\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.5lx\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %9.2p\n", 1234567));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %9.2p\n", 1234567) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %2.9p\n", 1234));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %2.9p\n", 1234) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%3*p}\n", 10, 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%3*p}\n", 10, 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#-08x\n", 42));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#-08x\n", 42) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%10R}\n"));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%10R}\n") - 3);
//
//	printf("\nsize= %d\n", printf("printf: %10R\n"));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %10R\n") - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.10R\n"));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %.10R\n") - 3);
//
//	printf("\nsize= %d\n", printf("printf: %5s, %.5s\n", "Coucou", "Coucou"));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %5s, %.5s\n", "Coucou", "Coucou") - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%05.s}\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%05.s}\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%07s}\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%07s}\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%05s}\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%05s}\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%.5s}\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%.5s}\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.3o\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.3o\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.1o\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.1o\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#3o\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#3o\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.3o\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.3o\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.o\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.o\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.3o\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.3o\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.o\n", 1));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.o\n", 1) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#o\n", 40));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#o\n", 40) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %o\n", 40));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", 40) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %o\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#.o %#.0o\n", 0, 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#.o %#.0o\n", 0, 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %.o %.0o\n", 0, 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %.o %.0o\n", 0, 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#o\n", 0));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#o\n", 0) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %####0000 33..1d\n", 256));
//	printf("\nsize= %d\n", printf("printf: %####000033..1d\n", 256));
//	printf("\nsize= %d\n", printf("printf: %####000 33..1d\n", 256));
//	printf("\nsize= %d\n", printf("printf: %0000 33..1d\n", 256));
//	printf("\nsize= %d\n", printf("printf: %####0000 33..d\n", 256));
//	printf("\nsize= %d\n", printf("printf: %####0000 33d\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %####0000 33..1d\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#033.d\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#033.d\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %####0000 33..1x\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %####0000 33..1x\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %#033.x\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#033.x\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %###-#0000 33...12..#0+0d\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %###-#0000 33...12..#0+0d\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %###+#0000 33...12..#0-0d\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %###+#0000 33...12..#0-0d\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: %###-#0000 33...12..#00d\n", 256));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %###-#0000 33...12..#00d\n", 256) - 3);
//
//	printf("\nsize= %d\n", printf("printf: {%-15Z}\n", 123));
//	printf("\nsize= %d\n", ft_printf("ft_printf: {%-15Z}\n", 123) - 3);
//
//	int tab[10];
//	tab[0] = 1;
//	tab[1] = 2;
//	tab[2] = 3;
//	tab[3] = 4;
//	tab[4] = 5;
//	tab[5] = 6;
//	tab[6] = 7;
//	tab[7] = 8;
//	tab[8] = 10;
//	tab[9] = 0;
//	printf("\nsize= %d\n", ft_printf("%a\n", tab));
//
//	tab[0] = 'a';
//	tab[1] = 'b';
//	tab[2] = 'c';
//	tab[3] = 'd';
//	tab[4] = 'e';
//	tab[5] = 'f';
//	tab[6] = 'g';
//	tab[7] = 'h';
//	tab[8] = 'i';
//	tab[9] = 0;
//	printf("\nsize= %d\n", ft_printf("%a\n", tab));
//
//	char **array;
//	array = malloc(sizeof(char*) * 4);
//	array[0] = malloc(sizeof(char) * 4);
//	array[0][0] = 'L';
//	array[0][1] = 'o';
//	array[0][2] = 'L';
//	array[0][3] = '\0';
//	array[1] = malloc(sizeof(char) * 4);
//	array[1][0] = 'X';
//	array[1][1] = 'd';
//	array[1][2] = 'X';
//	array[1][3] = '\0';
//	array[2] = malloc(sizeof(char) * 4);
//	array[2][0] = 'y';
//	array[2][1] = 'p';
//	array[2][2] = 'y';
//	array[2][3] = '\0';
//	array[3] = malloc(1);
//	array[3] = 0;
//	printf("\nsize= %d\n", ft_printf("%A\n", array));
//
//
//	printf("------ %%o ------\n");
//	printf("\nsize= %d\n", printf("printf: %o\n", 10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", 10));
//	printf("\nsize= %d\n", printf("printf: %o\n", -10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", -10));
//	printf("------- %%x -----\n");
//	printf("\nsize= %d\n", printf("printf: %x\n", 10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %x\n", 10));
//	printf("\nsize= %d\n", printf("printf: %x\n", -10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %x\n", -10));
//	printf("------- %%X -----\n");
//	printf("\nsize= %d\n", printf("printf: %X\n", 10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %X\n", 10));
//	printf("\nsize= %d\n", printf("printf: %X\n", -10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %X\n", -10));
//	printf("------- %%u -----\n");
//	printf("\nsize= %d\n", printf("printf: %u\n", 10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %u\n", 10));
//	printf("\nsize= %d\n", printf("printf: %u\n", -10));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %u\n", -10));
//	printf("------- %%-s -----\n");
//	printf("\nsize= %d\n", printf("printf: %s %-8s %s\n", "coucou", "ca", "va"));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %s %-8s %s\n", "coucou", "ca", "va"));
//	printf("------- %%#x -----\n");
//	char *s = "eee";
//	printf("\nsize= %d\n", printf("printf: %#x\n", &s));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#x\n", &s));
//	printf("------- %%#lx -----\n");
//	printf("\nsize= %d\n", printf("printf: %#lx\n", &s));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %#lx\n", &s));
//	printf("------- %%p -----\n");
//	printf("\nsize= %d\n", printf("printf: %p\n", &s));
//	printf("\nsize= %d\n", ft_printf("ft_printf: %p\n", &s));
//
//	printf("------- %%2c -----\n");
//	printf("\nsize= %d", printf("printf: %2c\n", 'a'));
//	printf("\nsize= %d", ft_printf("ft_printf: %2c\n", 'a'));
//	printf("\nsize= %d", printf("printf: %-2c\n", 'a'));
//	printf("\nsize= %d", ft_printf("ft_printf: %-2c\n", 'a'));
//
//	printf("------- %%2.0c -----\n");
//	printf("\nsize= %d", printf("printf: %2.0c\n", 'a'));
//	printf("\nsize= %d", ft_printf("ft_printf: %2.0c\n", 'a'));
//	printf("\nsize= %d", printf("printf: %-2.0c\n", 'a'));
//	printf("\nsize= %d", ft_printf("ft_printf: %-2.0c\n", 'a'));
//
//	printf("------- %%s -----\n");
//	printf("\nsize= %d", printf("printf: %s\n", "salut 😀 㗫  \u35EB"));
//	printf("\nsize= %d", ft_printf("ft_printf: %s\n", "salut 😀 㗫  \u35EB"));
//
//
//
//	printf("------- %%x -----\n");
//	printf("\nsize= %d", printf("printf: %x\n", 30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %x\n", 30482));
//	printf("\nsize= %d", printf("printf: %x\n", -30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %x\n", -30482));
//
//	printf("------- %%hhx -----\n");
//	printf("\nsize= %d", printf("printf: %hhx\n", 30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %hhx\n", 30482));
//	printf("\nsize= %d", printf("printf: %hhx\n", -30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %hhx\n", -30482));
//
//	printf("------- %%hx -----\n");
//	printf("\nsize= %d", printf("printf: %hx\n", 30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %hx\n", 30482));
//	printf("\nsize= %d", printf("printf: %hx\n", -30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %hx\n", -30482));
//
//	printf("------- %%lx -----\n");
//	printf("\nsize= %d", printf("printf: %lx\n", (unsigned long int)30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %lx\n", (unsigned long int)30482));
//	printf("\nsize= %d", printf("printf: %lx\n", (unsigned long int)-30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %lx\n", (unsigned long int)-30482));
//
//	printf("------- %%llx -----\n");
//	printf("\nsize= %d", printf("printf: %llx\n", (unsigned long long int)30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %llx\n", (unsigned long long int)30482));
//	printf("\nsize= %d", printf("printf: %llx\n", (unsigned long long int)-30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %llx\n", (unsigned long long int)-30482));
//
//	printf("------- %%jx -----\n");
//	printf("\nsize= %d", printf("printf: %jx\n", (uintmax_t)30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %jx\n", (intmax_t)30482));
//	printf("\nsize= %d", printf("printf: %jx\n", (uintmax_t)-30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %jx\n", (uintmax_t)-30482));
//
//	printf("------- %%zx -----\n");
//	printf("\nsize= %d", printf("printf: %zx\n", (size_t)30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %zx\n", (size_t)30482));
//	printf("\nsize= %d", printf("printf: %zx\n", (size_t)-30482));
//	printf("\nsize= %d", ft_printf("ft_printf: %zx\n", (size_t)-30482));

	return (0);
}
