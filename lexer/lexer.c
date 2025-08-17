/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:30:00 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:50:08 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_token_buffer(const char *input, int *j, char *buffer, t_quote *q)
{
	int	len;

	len = 0;
	while (input[*j] && !ft_isspace(input[*j]) && !is_operator_start(input[*j]))
	{
		if (is_quote(input[*j]))
		{
			if (!handle_quote(input, j, buffer + len, q))
				return (0);
			len += ft_strlen(buffer + len);
		}
		else
		{
			buffer[len] = input[*j];
			len++;
			(*j)++;
		}
	}
	buffer[len] = '\0';
	return (1);
}

t_lexer_result	extract_token(const char *input, int i)
{
	int		j;
	char	buffer[4096];
	t_token	*token;
	t_quote	q;

	j = i;
	init_quote(&q);
	if (!fill_token_buffer(input, &j, buffer, &q))
		return ((t_lexer_result){NULL, -1});
	token = create_token(buffer, WORD);
	if (!token)
		return ((t_lexer_result){NULL, -1});
	set_token_quote(token, &q);
	token->expandable = ft_strchr(token->value, '$') != NULL
		&& token->quote != SINGLE_QUOTE;
	return ((t_lexer_result){token, j});
}

int	handle_operator(t_data *data, const char *input, int *i)
{
	char			op[3];
	t_token_type	type;
	t_token			*token;
	int				len;

	op[0] = 0;
	op[1] = 0;
	op[2] = 0;
	len = verify_operator_type(input, *i, &type);
	if (!len)
		return (printf("Unknown operator: %c\n", input[*i]), 0);
	op[0] = input[*i];
	op[1] = input[*i + 1];
	token = create_token((const char *)op, type);
	if (!token)
	{
		free_list(data->token_head, get_next_token,
			(void (*)(void *))free_token_node);
		return (0);
	}
	add_token(&data->token_head, token);
	*i += len;
	return (1);
}

int	handle_token(t_data *data, const char *input, int *i)
{
	t_lexer_result	result;

	result = extract_token(input, *i);
	if (result.index == -1)
	{
		if (result.token)
			free_single_token(result.token);
		return (0);
	}
	if (result.token)
		add_token(&data->token_head, result.token);
	*i = result.index;
	return (1);
}

void	*lexer(t_data *data, const char *input)
{
	int		i;

	data->token_head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (is_operator_start(input[i]))
		{
			if (!handle_operator(data, input, &i))
				return (NULL);
			continue ;
		}
		if (!handle_token(data, input, &i))
			return (NULL);
	}
	return (data->token_head);
}
