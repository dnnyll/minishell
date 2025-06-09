/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:57:27 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/05 14:32:14 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *)s;
	while (n > 0)
	{
		*a = 0;
		a++;
		n--;
	}
}
/*
#include <stdio.h>

int	main (void)
{
	char str[] = "danny sucks at coding";

	ft_bzero(str + 11, 6);
	printf("%s\n", str);
}
*/
