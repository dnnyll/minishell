/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:34:28 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 11:07:24 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_length(t_token_type type)
{
	// printf("get_operator_length\n");
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		return (2);
	return (1);
}

t_token_type	get_operator_type(const char *input)
{
	// printf("get_operator_type\n");
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

t_token_result	extract_operator(const char *input, int i)
{
	// printf("extract_operator\n");
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
