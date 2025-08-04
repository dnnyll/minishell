#include "minishell.h"

//	Purpose: Finds the length of a quoted string, stopping at the matching closing quote.
int	get_quoted_length(const char *input, char quote_char)
{
	int	len;
	
	len = 0;
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
		return (free(value), NULL);		
	ft_strlcpy(value, input, len + 1);	// Copy substring up to `len`
	return (value);
}

//	Purpose: Handles a quoted token, strips the quotes, and creates a token with the correct quote type
t_lexer_result	extract_quoted(const char *input, int i)
{
	t_lexer_result	res;
	t_token			*token;
	char			*token_value;
	char			quote_start;
	int				len;

	quote_start = input[i];								// Save which quote character started this
	printf("quote_start = %c\n\n\n", quote);
	len = get_quoted_length(input + i + 1, quote);	// Find closing quote
	if (len == -1)
	{
		print_error("minishell: unmatched quote\n", NULL, NULL);
		return ((t_lexer_result){NULL, -1});		// Abort lexer
	}
	token_value = ft_substr(input, i + 1, len);		// Copy string between quotes
	if (!token_value)
		return ((t_lexer_result){NULL, i});
	token = create_token(token_value, WORD);
	if (!token)
		return ((t_lexer_result){NULL, i});
	if (quote_start == '\'')
		token->quote = SINGLE_QUOTE;
	else
		token->quote = DOUBLE_QUOTE;
	res.token = token;
	res.index = i + len + 2;					// Move index past both quotes
	return (res);
}
