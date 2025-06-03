/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:02:37 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 15:48:12 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}
/*
int	main(void)
{
	const char str[] = "zankou na tenshi no you ni,";
	int c = 107;  // ASCII value of 'k'
	char *result = ft_strchr(str, c);
    
	if (result)
		printf("Found: %c\n", *result);
	else
		printf("Character not found.\n");
	return (0);
}
*/
