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
	data->token_head = NULL;
}
