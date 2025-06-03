/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:48:09 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/19 16:13:31 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *s, char c)
{
	size_t	i;
	size_t	b;
	size_t	count;

	i = 0;
	count = 0;
	b = 0;
	while (s[i])
	{
		if (s[i] == c)
			b = 0;
		else if (b == 0)
		{
			b = 1;
			count++;
		}
		i++;
	}
	return (count);
}

size_t	word_len(const char *s, unsigned int *start, char c)
{
	size_t	len;

	len = 0;
	while (s[*start] && s[*start] != c)
	{
		(*start)++;
		len++;
	}
	return (len);
}

char	**free_array(char **result, int arr_i)
{
	int	i;

	i = 0;
	while (i < arr_i)
	{
		free (result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

void	init(unsigned int *start, size_t *i, size_t *len)
{
	*start = 0;
	*i = 0;
	*len = 0;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	start;
	size_t			w_count;
	size_t			i;
	size_t			len;
	char			**result;

	w_count = word_count(s, c);
	init(&start, &i, &len);
	result = malloc((w_count + 1) * (sizeof(char *)));
	if (!result)
		return (NULL);
	while (i < w_count)
	{
		while (s[start] && s[start] == c)
			start++;
		if (s[start])
		{
			len = word_len(s, &start, c);
			result[i] = ft_substr(s, start - len, len);
			if (!result[i])
				return (free_array(result, i));
			i++;
		}
	}
	return (result[i] = NULL, result);
}
/*
int main() 
{
    const char *str = "   cake   ";
    char delimiter = ' ';
    char **result;
    size_t i = 0;

    // Call your ft_split function
    result = ft_split(str, delimiter);
    // Check if the result is NULL
    if (!result) {
        printf("Memory allocation failed.\n");
        return 1; // Exit if memory allocation failed
    }
    // Print the resulting split strings
    while (result[i]) {
        printf("result[%zu] = %s\n", i, result[i]);
        free(result[i]); // Free each string after use
        i++;
    }
    free(result); // Free the result array itself
    return 0; // Indicate successful execution
}
*/
