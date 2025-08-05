#include "minishell.h"

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