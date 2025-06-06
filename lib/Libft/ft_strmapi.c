/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:39:47 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 18:57:59 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*result;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			result[i] = f(i, s[i]);
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}
/*
int	main (void)
{
	char s[] = "twoja stara le parkour";
*/
