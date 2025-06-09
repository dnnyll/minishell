/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:49:03 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 19:02:04 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	match(const char *h, const char *n, size_t len)
{
	size_t	i;

	i = 0;
	while (n[i] && h[i] && i < len && h[i] == n[i])
		i++;
	return (n[i] == '\0');
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len)
	{
		if (match(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
/*
int main(void)
{
    char str1[] = "please have a cookie";
    char str2[] = "cookie";
    char *result;

    result = ft_strnstr(str1, str2, 21);

    if (result != NULL)
        printf("Found: %s\n", result);
    else
        printf("Not found.\n");

    return (0);
}
*/
