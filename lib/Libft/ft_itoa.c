/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:20:51 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 18:46:26 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_num(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	nbr;

	len = ft_count_num(n);
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
		str[0] = '-';
	while (len-- > (n < 0))
	{
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
