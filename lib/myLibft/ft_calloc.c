/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:14:46 by daniefe2          #+#    #+#             */
/*   Updated: 2024/10/18 18:44:38 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc (count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero (result, count * size);
	return (result);
}
/*
int main(void)
{
    int *arr;
    size_t count = 5;
    size_t size = sizeof(int);

    // Test ft_calloc by allocating memory for 5 integers
    arr = (int *)ft_calloc(count, size);

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1; // Exit if allocation failed
    }

    // Print the values manually
    printf("arr[0] = %d\n", arr[0]);
    printf("arr[1] = %d\n", arr[1]);
    printf("arr[2] = %d\n", arr[2]);
    printf("arr[3] = %d\n", arr[3]);
    printf("arr[4] = %d\n", arr[4]);

    // Free the allocated memory
    free(arr);

    return 0;
}
*/
