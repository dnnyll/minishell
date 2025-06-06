/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:59:54 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 18:49:35 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		character;

	src = (const unsigned char *)s;
	character = (unsigned char)c;
	while (n--)
	{
		if (*src == character)
			return ((void *)src);
		src++;
	}
	return (NULL);
}
/*
int	main (void)
{
	const char	str[] = "zankou na tenshi no you ni,";
	ft_memchr(str, 107, 28);
}
*/
