/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:32:19 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 18:52:35 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	i = 0;
	if (s && f)
	{
		while (*s)
		{
			f(i, s);
			{
				i++;
				s++;
			}
		}
	}
}
/*
// A function to use with ft_striteri, printing each character and its index
void print_char(unsigned int i, char *c)
{
    printf("Index %u: %c\n", i, *c);
}

// A function to convert each character to uppercase
void to_upper(unsigned int i, char *c)
{
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;  // Convert lowercase to uppercase
}

int main(void)
{
    char str[] = "hello world!";
    
    printf("Testing print_char function:\n");
    ft_striteri(str, print_char); // Applies print_char to each character

    printf("\nBefore to_upper: %s\n", str);
    ft_striteri(str, to_upper); // Applies to_upper to modify the string
    printf("After to_upper: %s\n", str);

    return 0;
}
*/
