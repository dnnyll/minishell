/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:55:08 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/03 14:16:22 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;	

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
int	main (void)
{
	const char	str[] = "danny sucks at coding";
	ft_strlen(str);
}
*/