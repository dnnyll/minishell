/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:32:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/24 14:50:42 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Purpose: Checks if the character is a shell operator (|, <, or >).
int	is_operator_char(char c)
{
	// printf("is_operator_char\n");
	return (c == '|' || c == '<' || c == '>');
}

//	Purpose: Calculates the length of a word until whitespace or an operator.
int	get_word_length(const char *input)
{
	// Keep counting until we hit space or operator
	int	len;
	
	len = 0;
	while (input[len] && !ft_isspace(input[len]) && !is_operator_char(input[len]))
		len++;
	return (len);
}

//	Purpose: Extracts a plain word (not quoted, not an operator) from the input.
t_lexer_result	extract_word(const char *input, int i)
{
	// printf()
	t_lexer_result	result;
	int				len;

	len = get_word_length(input + i);				// Get word length starting from i
	// Allocate memory for the token
	result.token = malloc(sizeof(t_token));
	if (!result.token)
		return ((t_lexer_result){NULL, i});
	// Allocate memory for the token's string value
	result.token->value = malloc(len + 1);
	if (!result.token->value)
	{
		free(result.token);
		return ((t_lexer_result){NULL, i});
	}
	// Copy the word from input into token->value
	ft_strlcpy(result.token->value, input + i, len + 1);
	// Set token fields
	result.token->type = WORD;
	result.token->quote = NO_QUOTE;					// It's a plain word, not quoted
	result.token->next = NULL;
	// Update index to the position after the word
	result.index = i + len;
	return (result);
}




