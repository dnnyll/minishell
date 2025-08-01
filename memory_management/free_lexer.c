#include "minishell.h"

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