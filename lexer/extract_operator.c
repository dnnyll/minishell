/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:28 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/27 12:29:16 by daniefe2         ###   ########.fr       */
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

t_token	*create_token(const char *value, t_token_type type)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return(NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
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
	t_token_type	type;
	int				len;
	char			op[3];

	type = get_operator_type(&input[i]);
	if (type == TOKEN_ERROR)
	{
		res.token = NULL;
		res.new_index = i;
		return (res);
	}
	len = get_operator_length(type);
	op[0] = input[i];
	op[1] = '\0';
	op[2] = '\0';
	if (len == 2)
		op[1] = input[i + 1];
	res.token = create_token(op, type);
	if (res.token)
		res.new_index = i + len;
	else
		res.new_index = i;
	return (res);
}
