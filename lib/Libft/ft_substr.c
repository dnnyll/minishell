/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:00:38 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 19:05:23 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*sub_s;

	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (s_len < start)
		len = 0;
	if (s_len - start < len)
		len = s_len - start;
	sub_s = ft_calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
/*
int	main (void)
{
	char	str [] = "eva-01";
	ft_substr(str, 4, 6);
}
*/
