#include "minishell.h"

// Frees all tokens from data->token_head
void	free_tokens(t_data *data)
{
	t_token	*token;
	t_token	*next;

	token = data->token_head;
	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
	data->token_head = NULL; // Clear reference in data
}

const	char *token_type_str(t_token_type type)
{
	if (type == CMD) return "COMMAND";
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == HEREDOC) return "HEREDOC";
	if (type == APPEND) return "APPEND";
	if (type == ERROR) return "ERROR";
	// if (type == T_EOF) return "EOF";
	// if (type == ENV) return "ENV";
	return ("UNKNOWN");
}

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

//	Purpose: Frees all memory allocated for the token list.
void	free_token_list(t_token *token)
{
	t_token *next;

	while (token)
	{
		next = token->next;				// Save pointer to the next token
		free(token->value);				// Free the string inside the token
		free(token);					// Free the token itself
		token = next;					// Move to the next token
	}
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
