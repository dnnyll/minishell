/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:32:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 11:22:35 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_char(char c)
{
	// printf("is_operator_char\n");
	return (c == '|' || c == '<' || c == '>');
}

int	get_word_length(const char *input)
{
	// printf("get_operator_type\n");
	int	len;
	
	len = 0;
	while (input[len] && !ft_isspace(input[len]) && !is_operator_char(input[len]))
		len++;
	return (len);
}

t_token_result	extract_word(const char *input, int i)
{
	// printf("extract_word\n");
	t_token_result	result;
	int				len;

	len = get_word_length(input + i);
	result.token = malloc(sizeof(t_token));
	if (!result.token)
		return ((t_token_result){NULL, i});
	result.token->value = malloc(len + 1);
	if (!result.token->value)
	{
		free(result.token);
		return ((t_token_result){NULL, i});
	}
	ft_strlcpy(result.token->value, input + i, len + 1);
	result.token->type = TOKEN_WORD;
	result.token->next = NULL;
	result.new_index = i + len;
	return (result);
}



