/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:32:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/27 07:27:52 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	get_word_length(const char *input)
{
	int	len;
	
	len = 0;
	while (input[len] && !ft_isspace(input[len]) && !is_operator_char(input[len]))
		len++;
	return (len);
}
/*
	Gets word length using get_word_length.
	Allocates a t_token.
	Allocates memory for the token's value (len + 1 for null-terminator).
	Copies the word into the token using ft_strlcpy.
	Sets the token type to TOKEN_WORD.
	Sets the new_index to i + len (to continue scanning after this word).
*/
t_token_result	extract_word(const char *input, int i)
{
	t_token_result	res;
	int				len;

	len = get_word_length(input + i);
	res.token = malloc(sizeof(t_token));
	if (!res.token)
		return ((t_token_result){NULL, i});
	res.token->value = malloc(len + 1);
	if (!res.token->value)
	{
		free(res.token);
		return ((t_token_result){NULL, i});
	}
	ft_strlcpy(res.token->value, input + i, len + 1);
	res.token->type = TOKEN_WORD;
	res.token->next = NULL;
	res.new_index = i + len;
	return (res);
}



