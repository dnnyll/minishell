#include "minishell.h"

void	free_token_node(t_token *token)
{
	free(token->value);
	free(token);
}

void	*get_next_token(void *node)
{
	return ((t_token *)node)->next;
}

void	free_tokens(t_data *data)
{
	free_list(data->token_head, get_next_token,
		(void (*)(void *))free_token_node);
	data->token_head = NULL;
}

void	free_single_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
		free(token->value);
	free(token);
}

void	free_lexer_result(t_lexer_result *result)
{
	printf("free_lexer_result\n");
	if (!result)
		return ;
	if (result->token)
		free(result->token);
	free(result);
}
