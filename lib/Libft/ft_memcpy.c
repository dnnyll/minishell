/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:38:41 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/19 16:07:14 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	unsigned char		*a;
	unsigned const char	*b;
	int					i;

	if (!dst && !src)
		return (NULL);
	a = (unsigned char *)dst;
	b = (unsigned const char *)src;
	i = 0;
	while (len--)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
/*

int	main (void)
{
//	char	dest[] = "danny sucks at coding";
	char	src[] = "danny SUCKS at coding";
	ft_memcpy(((void *)0), ((void *)0), 0);
	printf("%s\n", src);
}
*/
