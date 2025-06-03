/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:57:27 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 15:10:29 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;

	a = (unsigned char *)b;
	while (len--)
		*a++ = (unsigned char)c;
	return (b);
}
/*
#include <stdio.h>

int	main(void)
{
	char	str[] = "danny sucks at coding";
	unsigned int len = 5;

	ft_memset(str + 6, 'x', len);
	printf("%s\n", str);
}
*/
