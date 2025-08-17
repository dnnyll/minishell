/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:29:42 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:38:00 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quote(t_quote *q)
{
	q->value = 0;
	q->is_quoted = 0;
}

int	handle_quote(const char *input, int *j, char *buffer, t_quote *q)
{
	int	k;

	k = 0;
	q->is_quoted = 1;
	q->value = input[*j];
	(*j)++;
	while (input[*j] && input[*j] != q->value)
	{
		buffer[k] = input[*j];
		k++;
		(*j)++;
	}
	if (input[*j] != q->value)
		return (0);
	(*j)++;
	buffer[k] = '\0';
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
