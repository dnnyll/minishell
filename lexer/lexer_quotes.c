#include "minishell.h"

void	init_quote(t_quote *q)
{
	q->value = 0;
	q->is_quoted = 0;
}

int	handle_quote(const char *input, int *j, char *buffer, int *len, t_quote *q)
{
	q->is_quoted = 1;
	q->value = input[*j];
	(*j)++;
	while (input[*j] && input[*j] != q->value)
	{
		buffer[*len] = input[*j];
		(*len)++;
		(*j)++;
	}
	if (input[*j] != q->value)
		return (0);
	(*j)++;
	return (1);
}

void	set_token_quote(t_token *token, t_quote *q)
{
	if (!q->is_quoted)
		token->quote = NO_QUOTE;
	else if (q->value == '\'')
		token->quote = SINGLE_QUOTE;
	else if (q->value == '"')
		token->quote = DOUBLE_QUOTE;
	else
		token->quote = NO_QUOTE;
}