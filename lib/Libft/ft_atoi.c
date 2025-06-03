/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:48:30 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/08 11:05:39 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
/*
int	main(void)
{
	const char *test_cases[] = {
		"42",
		"   -42",
		"   +12345",
		"   000123",
		"123abc",
		"-123abc",
		"  +0",
		"  -2147483648",  // Min int
		"  2147483647",   // Max int
		"   \t\n\v\f\r 567",  // With mixed whitespace characters
		"   +---42",  // Invalid input after sign
		NULL          // End of test cases
	};

	int i = 0;
	while (test_cases[i])
	{
		printf("Input: '%s'\n", test_cases[i]);
		printf("Output: %d\n\n", ft_atoi(test_cases[i]));
		i++;
	}

	return 0;
}
*/
