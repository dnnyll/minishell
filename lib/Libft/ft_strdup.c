/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:43:35 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 11:41:05 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	size;

	size = ft_strlen(s1) + 1;
	result = malloc(sizeof(char) * size);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, size);
	return (result);
}
/*
int	main (void)
{
	char	*result;
	result = ft_strdup("danny sucks at coding..");
	printf("%s\n", result);
	free (result);
}
*/
