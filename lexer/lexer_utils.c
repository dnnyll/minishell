/* **************************************************************************** */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                           DEAD INSIDE                                        */
/*                                                                              */
/*                                                                              */
/*                                       MROSSET & DANIEFE2                     */
/*                                                                              */
/*                                                                              */
/* **************************************************************************** */

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

int	verify_operator_type(const char *input, int i, t_token_type *type)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (*type = APPEND, 2);
		return (*type = REDIR_OUT, 1);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (*type = HEREDOC, 2);
		return (*type = REDIR_IN, 1);
	}
	if (input[i] == '|')
		return (*type = PIPE, 1);
	return (0);
}
