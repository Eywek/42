/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 20:25:54 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/23 20:11:20 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include "includes/core.h"
#include "tests/functions.h"

int main(int argc, char *argv[])
{
	//launch_tests();
	//return (0);

	char *s = "Coucou";
	printf("Result = %d chars\n", ft_printf("Coucoy %5.2s %-2% ca va ?\nTu as %03d ans\nLol %d c\nPointer: %p\n", "Valentin", 18, 5, &s));

	printf("------ %%o ------\n");
	printf("\nsize= %d\n", printf("printf: %o\n", 10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", 10));
	printf("\nsize= %d\n", printf("printf: %o\n", -10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %o\n", -10));
	printf("------- %%x -----\n");
	printf("\nsize= %d\n", printf("printf: %x\n", 10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %x\n", 10));
	printf("\nsize= %d\n", printf("printf: %x\n", -10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %x\n", -10));
	printf("------- %%X -----\n");
	printf("\nsize= %d\n", printf("printf: %X\n", 10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %X\n", 10));
	printf("\nsize= %d\n", printf("printf: %X\n", -10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %X\n", -10));
	printf("------- %%u -----\n");
	printf("\nsize= %d\n", printf("printf: %u\n", 10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %u\n", 10));
	printf("\nsize= %d\n", printf("printf: %u\n", -10));
	printf("\nsize= %d\n", ft_printf("ft_printf: %u\n", -10));
	printf("------- %%-s -----\n");
	printf("\nsize= %d\n", printf("printf: %s %-8s %s\n", "coucou", "ca", "va"));
	printf("\nsize= %d\n", ft_printf("ft_printf: %s %-8s %s\n", "coucou", "ca", "va"));
	printf("------- %%#x -----\n");
	printf("\nsize= %d\n", printf("printf: %#x\n", &s));
	printf("\nsize= %d\n", ft_printf("ft_printf: %#x\n", &s));
	printf("------- %%#lx -----\n");
	printf("\nsize= %d\n", printf("printf: %#lx\n", &s));
	printf("\nsize= %d\n", ft_printf("ft_printf: %#lx\n", &s));
	printf("------- %%p -----\n");
	printf("\nsize= %d\n", printf("printf: %p\n", &s));
	printf("\nsize= %d\n", ft_printf("ft_printf: %p\n", &s));

	printf("------- %%2c -----\n");
	printf("\nsize= %d", printf("printf: %2c\n", 'a'));
	printf("\nsize= %d", ft_printf("ft_printf: %2c\n", 'a'));
	printf("\nsize= %d", printf("printf: %-2c\n", 'a'));
	printf("\nsize= %d", ft_printf("ft_printf: %-2c\n", 'a'));

	printf("------- %%2.0c -----\n");
	printf("\nsize= %d", printf("printf: %2.0c\n", 'a'));
	printf("\nsize= %d", ft_printf("ft_printf: %2.0c\n", 'a'));
	printf("\nsize= %d", printf("printf: %-2.0c\n", 'a'));
	printf("\nsize= %d", ft_printf("ft_printf: %-2.0c\n", 'a'));

	printf("------- %%s -----\n");
	printf("\nsize= %d", printf("printf: %s\n", "salut 😀 㗫  \u35EB"));
	printf("\nsize= %d", ft_printf("ft_printf: %s\n", "salut 😀 㗫  \u35EB"));



	printf("------- %%x -----\n");
	printf("\nsize= %d", printf("printf: %x\n", 30482));
	printf("\nsize= %d", ft_printf("ft_printf: %x\n", 30482));
	printf("\nsize= %d", printf("printf: %x\n", -30482));
	printf("\nsize= %d", ft_printf("ft_printf: %x\n", -30482));

	printf("------- %%hhx -----\n");
	printf("\nsize= %d", printf("printf: %hhx\n", 30482));
	printf("\nsize= %d", ft_printf("ft_printf: %hhx\n", 30482));
	printf("\nsize= %d", printf("printf: %hhx\n", -30482));
	printf("\nsize= %d", ft_printf("ft_printf: %hhx\n", -30482));

	printf("------- %%hx -----\n");
	printf("\nsize= %d", printf("printf: %hx\n", 30482));
	printf("\nsize= %d", ft_printf("ft_printf: %hx\n", 30482));
	printf("\nsize= %d", printf("printf: %hx\n", -30482));
	printf("\nsize= %d", ft_printf("ft_printf: %hx\n", -30482));

	printf("------- %%lx -----\n");
	printf("\nsize= %d", printf("printf: %lx\n", (unsigned long int)30482));
	printf("\nsize= %d", ft_printf("ft_printf: %lx\n", (unsigned long int)30482));
	printf("\nsize= %d", printf("printf: %lx\n", (unsigned long int)-30482));
	printf("\nsize= %d", ft_printf("ft_printf: %lx\n", (unsigned long int)-30482));

	printf("------- %%llx -----\n");
	printf("\nsize= %d", printf("printf: %llx\n", (unsigned long long int)30482));
	printf("\nsize= %d", ft_printf("ft_printf: %llx\n", (unsigned long long int)30482));
	printf("\nsize= %d", printf("printf: %llx\n", (unsigned long long int)-30482));
	printf("\nsize= %d", ft_printf("ft_printf: %llx\n", (unsigned long long int)-30482));

	printf("------- %%jx -----\n");
	printf("\nsize= %d", printf("printf: %jx\n", (uintmax_t)30482));
	printf("\nsize= %d", ft_printf("ft_printf: %jx\n", (intmax_t)30482));
	printf("\nsize= %d", printf("printf: %jx\n", (uintmax_t)-30482));
	printf("\nsize= %d", ft_printf("ft_printf: %jx\n", (uintmax_t)-30482));

	printf("------- %%zx -----\n");
	printf("\nsize= %d", printf("printf: %zx\n", (size_t)30482));
	printf("\nsize= %d", ft_printf("ft_printf: %zx\n", (size_t)30482));
	printf("\nsize= %d", printf("printf: %zx\n", (size_t)-30482));
	printf("\nsize= %d", ft_printf("ft_printf: %zx\n", (size_t)-30482));

	return (0);
}
