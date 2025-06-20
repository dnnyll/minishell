/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:57:58 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/20 11:49:53 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Purpose: Finds the length of a quoted string, stopping at the matching closing quote.
int	get_quoted_length(const char *input, char quote_char)
{
	int	len = 0;

	while (input[len])					// Loop until null terminator
	{
		if (input[len] == quote_char)	// Found matching quote
			return (len);				// Return distance to quote
		len++;
	}
	return (-1);						// No closing quote found → syntax error
}

//	Purpose: Allocates and copies a quoted string (without quotes).
char	*extract_quoted_value(const char *input, int len)
{
	char	*value;
	
	value = malloc(len + 1);			// Allocate memory for substring (+1 for null terminator)
	if (!value)
		return (NULL);
	ft_strlcpy(value, input, len + 1);	// Copy substring up to `len`
	return (value);
}

//	Purpose: Handles a quoted token, strips the quotes, and creates a token with the correct quote type
t_lexer_result	extract_quoted(const char *input, int i)
{
	t_lexer_result	res;
	t_token			*token;
	char			*token_value;
	char			quote;
	int				len;

	quote = input[i];								// Save which quote character started this
	len = get_quoted_length(input + i + 1, quote);	// Find closing quote
	if (len == -1)
	{
		fprintf(stderr, "syntax error: unterminated quote\n");
		return ((t_lexer_result){NULL, -1});		// Abort lexer
	}

	token_value = ft_substr(input, i + 1, len);		// Copy string between quotes
	if (!token_value)
		return ((t_lexer_result){NULL, i});

	token = create_token(token_value, WORD);	// Create token object
	free (token_value);								// Free temporary buffer after use

	if (!token)
		return ((t_lexer_result){NULL, i});

	// Save quote type info for later use (e.g., expansion rules)
	if (quote == '\'')
		token->quote = SINGLE_QUOTE;
	else
		token->quote = DOUBLE_QUOTE;

	res.token = token;
	res.index = i + len + 2;					// Move index past both quotes
	return (res);
}
