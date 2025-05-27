/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:28 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/27 07:28:27 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	Recognize what kind of operator appears at a given position in the input.
	Determine how many characters the operator takes.
	Create a new token for it.
	Return the token and the updated index (after skipping the operator).
*/
int	get_operator_length(t_token_type type)
{
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		return (2);
	return (1);
}


t_token_type	get_operator_type(const char *input)
{
	if (input[0] == '|' && input[1] != '|')
		return (TOKEN_PIPE);
	if (input[0] == '<' && input[1] == '<')
		return (TOKEN_HEREDOC);
	if (input[0] == '<')
		return (TOKEN_REDIR_IN);
	if (input[0] == '>' && input[1] == '>')
		return (TOKEN_APPEND);
	if (input[0] == '>')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_ERROR);
}



/*
	Calls get_operator_type() to identify the operator type at position i.
	Calls get_operator_length() to know how many characters the operator has.
	Allocates memory for a new t_token.
	Copies the operator characters (1 or 2) into the token's value.
	Sets the token type and returns it along with the updated index (i + len).
*/
	t_token_result	extract_operator(const char *input, int i)
{
	t_token_result	res;
	t_token			*token;
	t_token_type	type;
	int				len;

	type = get_operator_type(&input[i]);
	len = get_operator_length(type);
	token = malloc(sizeof(t_token));
	if (!token)
		return ((t_token_result){NULL, i});
	token->value = malloc(len + 1);
	if (!token->value)
	{
		free(token);
		return ((t_token_result){NULL, i});
	}
	token->value[0] = input[i];
	if (len == 2)
		token->value[1] = input[i + 1];
	token->value[len] = '\0';
	token->type = type;
	token->next = NULL;
	res.token = token;
	res.new_index = i + len;
	return (res);
}
