/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:04:59 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 19:03:03 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return ((char *)s + len);
		len--;
	}
	return (0);
}
/*
int main(void)
{
    const char str[] = "zankou na tenshi no you ni,";
    int c = 'a';
    char *result = ft_strrchr(str, c);
	printf("%s\n", result);
}
*/
