#include "minishell.h"

//	Purpose: Adds a new token to the end of the token list.
void	add_token(t_token **list, t_token *new_token)
{
	if (!list || !new_token)
		return ; // Do nothing if input is invali
	if (*list == NULL)
	{
		*list = new_token; // List is empty → set head to new token
		return ;
	}
	t_token *current = *list;
	while (current->next)
		current = current->next; // Traverse to the last token
	current->next = new_token; // Append new token to the end
}

//	Purpose: Creates and initializes a new token with the given value and type.
t_token	*create_token(const char *value, t_token_type type)
{
	t_token *token = malloc(sizeof(t_token));	// Allocate memory for token
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);			// Duplicate the string
	if (!token->value)
	{
		free(token);							// Clean up if strdup fails
		return (NULL);
	}
	token->type = type;							// Set token type (e.g., WORD)
	token->quote = NO_QUOTE;					// Default quote type
	token->next = NULL;							// No next token yet
	return (token);
}
