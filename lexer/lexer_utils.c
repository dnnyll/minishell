/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:29:50 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:38:08 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_operator_start(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	verify_operator_type(const char *input, int i, t_token_type *type)
{
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (*type = APPEND, 2);
		return (*type = REDIR_OUT, 1);
	}
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (*type = HEREDOC, 2);
		return (*type = REDIR_IN, 1);
	}
	if (input[i] == '|')
		return (*type = PIPE, 1);
	return (0);
}
