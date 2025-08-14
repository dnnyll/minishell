#include "minishell.h"

//	Purpose: Adds a new token to the end of the token list.
void	add_token(t_token **list, t_token *new_token)
{
	t_token	*current;

	if (!list || !new_token)
		return ;
	if (*list == NULL)
	{
		*list = new_token;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

//	Purpose: Creates and initializes a new token with the given value and type.
t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*token;

	token = init_token();
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	return (token);
}
