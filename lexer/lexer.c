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
	return (c == '|' || c == '<' || c == '>');	// $ sign might not need to be here!
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

void	free_lexer_result(t_lexer_result *result)
{
	if (!result)
		return;
	if (result->token)
		free(result->token);
	free(result);
}

void	free_single_token(t_token *token)
{
	if (!token)
		return;
	if (token->value)
		free(token->value);
	free(token);
}

//	Purpose: Main lexer function: loops through the input and builds a list of tokens.
void	*lexer(t_data *data, const char *input)
{
	data->token_head = NULL;
	int		i;

	i = 0;
	while (input[i])
	{
		printf("i = %d\n", i);
		while (input[i] && ft_isspace(input[i]))
			i++;											// Skip all whitespace
		if (input[i] == '\0')
			break ;											// End of input
		t_lexer_result result = extract_token(input, i);	// Extract next token
		printf("called extracted token\n");
		if (result.index == -1)								// Syntax error occurred (e.g., unmatched quote)
		{
			printf("index == -1\n");
			if (result.token)
				free_single_token(result.token);
			free_token_list(data->token_head);
			return (NULL);									// Abort and clean up
		}
		if (result.token)
		{
			printf("token\n");
			add_token(&data->token_head, result.token);		// Add token to the list
		}
		if (result.index <= i)
		{
			printf("ERROR: extract_token didn't advance input at i = %d\n", i);
			if (result.token)
				free_single_token(result.token);
			break; // prevent infinite loop
		}
		i = result.index;									// Move index past the token
	}
	return (data->token_head);
}
