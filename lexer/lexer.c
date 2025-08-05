#include "minishell.h"

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
				return err; // unmatched quote <----------------------------------- ?
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

// Handles shell operators like >, >>, <, <<, |
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
		free_token_list(data->token_head);
		return (0);
	}
	add_token(&data->token_head, token);
	*i += len;
	return (1);
}

// Handles word/quoted tokens using extract_token()
int	handle_token(t_data *data, const char *input, int *i)
{
	t_lexer_result	result;

	result = extract_token(input, *i);
	if (result.index == -1)
	{
		printf("DEBBUG: index == -1 @ lexer\n");
		if (result.token)
			free_single_token(result.token);
		free_token_list(data->token_head);
		return (0);
	}
	if (result.token)
	{
		//printf("token: %s\n", result.token->value);
		add_token(&data->token_head, result.token);
	}
	*i = result.index;
	return (1);
}

// main lexer loop
void	*lexer(t_data *data, const char *input)
{
	data->token_head = NULL;
	int		i = 0;

	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break;
		if (is_operator_start(input[i]))
		{
			if (!handle_operator(data, input, &i))
				return (NULL);
			continue;
		}
		if (!handle_token(data, input, &i))
			return (NULL);
	}
	return (data->token_head);
}

