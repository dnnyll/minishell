/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:22 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/13 11:23:04 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Purpose: Checks if a character is a whitespace (tabs, spaces, etc.).
int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || (c == 32))	// Matches tabs, newlines, space
		return (1);
	return (0);
}

//	Purpose: Checks if the character is a quote (' or ").
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

//	Purpose: Checks if the character is a shell operator (|, <, >, $).
int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '$');	// $ sign might not need to be here!
}

//	Purpose: Decides how to extract the token based on the current character.
t_lexer_result	extract_token(const char *input, int i)
{
	if (is_quote(input[i]))						// Quoted string → special extract
		return (extract_quoted(input, i));
	else if (is_operator_start(input[i]))		// Shell operator → handled separately
		return (extract_operator(input, i));
	else										// Regular word
		return (extract_word(input, i));
}

//	Purpose: Main lexer function: loops through the input and builds a list of tokens.
void	*lexer(t_data *data, const char *input)
{
	data->token_head = NULL;
	int		i = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;											// Skip all whitespace
		if (input[i] == '\0')
			break ;											// End of input
		t_lexer_result result = extract_token(input, i);	// Extract next token
		if (result.index == -1)							// Syntax error occurred (e.g., unmatched quote)
		{
			free_token_list(data->token_head);
			return (NULL);									// Abort and clean up
		}

		if (result.token)
			add_token(&data->token_head, result.token);		// Add token to the list

		i = result.index;								// Move index past the token
	}
	return (data->token_head);
}