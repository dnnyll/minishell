#include "minishell.h"

int	fill_token_buffer(const char *input, int *j, char *buffer, t_quote *q)
{
	int	len;

	len = 0;
	while (input[*j] && !ft_isspace(input[*j]) && !is_operator_start(input[*j]))
	{
		if (is_quote(input[*j]))
		{
			if (!handle_quote(input, j, buffer, &len, q))
				return (0);
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
	char			op[3] = {0};
	t_token_type	type;
	t_token			*token;
	int				len;

	len = verify_operator_type(input, *i, &type);
	if (!len)
	{
		printf("Unknown operator: %c\n", input[*i]);
		return (0);
	}
	op[0] = input[*i];
	op[1] = input[*i + 1];
	token = create_token(op, type);
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
		printf("DEBBUG: index == -1 @ lexer\n");
		if (result.token)
			free_single_token(result.token);
		free_list(data->token_head, get_next_token,
			(void (*)(void *))free_token_node);
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

/*
t_lexer_result extract_token(const char *input, int i)
{
	int		j = i;
	int		len = 0;
	char	buffer[4096]; // adjust if needed
	char	quote = 0;
	int		quoted = 0;
	t_token	*token;

	while (input[j] && !ft_isspace(input[j]) && !is_operator_start(input[j]))
	{
		if (is_quote(input[j]))
		{
			quoted = 1;
			quote = input[j];
			j++; // skip opening quote
			while (input[j] && input[j] != quote)
				buffer[len++] = input[j++];
			if (input[j] != quote)
			{
				t_lexer_result err = { NULL, -1 };
				return err; // unmatched quote <-------------------------- ?
			}
			j++; // skip closing quote
		}
		else
			buffer[len++] = input[j++];
	}
	buffer[len] = '\0';
	token = create_token(buffer, WORD);
	if (!token)
	{
		t_lexer_result err = { NULL, -1 };
		return err; //	<------------------------------------------ ?
	}
	if (quoted)
	{
		if (quote == '\'')
			token->quote = SINGLE_QUOTE;
		else if (quote == '"')
			token->quote = DOUBLE_QUOTE;
		else
			token->quote = NO_QUOTE;
	}
	else
	{
		token->quote = NO_QUOTE;
	}
	t_lexer_result result = { token, j };
	return (result);
}
*/
