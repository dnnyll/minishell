/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:47:50 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 19:04:48 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*result;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	result = malloc(sizeof(char) * (end - start + 1));
	if (result == NULL)
		return (NULL);
	while (i < end - start)
	{
		result[i] = s1[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
int	main (void)
{
	const char	*s1 = "xxHello Worldyy";
	printf("default s1: %s\n", s1);
	const char	*set = "xy";
	char 		*result;
	result = ft_strtrim(s1, set);
	printf("post trim: %s\n", result);
}
*/
/*
important note: when  you call ft_strchr and you it the arguments, you are
telling it to search the STRING (all the characters in it) for every letter
of the other string s1 at index [start], so start = 0, so it will compare
the character at that index to ALL the characters contained in the string
of letters you are searching (set).
*/
