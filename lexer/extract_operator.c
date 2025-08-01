#include "minishell.h"

int	get_operator_length(t_token_type type)
{
	// printf("get_operator_length\n");
	if (type == HEREDOC || type == APPEND)
		return (2);
	return (1);
}

t_token_type	get_operator_type(const char *input)
{
	// printf("get_operator_type\n");
	if (input[0] == '|')
		return (PIPE);
	if (input[0] == '|' && input[1] == '|')
		return (PIPE);
	if (input[0] == '<' && input[1] == '<')
		return (HEREDOC);
	if (input[0] == '<')
		return (REDIR_IN);
	if (input[0] == '>' && input[1] == '>')
		return (APPEND);
	if (input[0] == '>')
		return (REDIR_OUT);
	return (ERROR);
}
t_lexer_result extract_operator(const char *input, int i)
{
	// printf("extract_operator\n");
	t_lexer_result	result;
	t_token_type	type;
	int				len;
	char			op[3];

	type = get_operator_type(&input[i]);
	if (type == ERROR)
	{
		// Extract the invalid operator char anyway, so the lexer keeps moving
		op[0] = input[i];
		op[1] = '\0';
		result.token = create_token(op, ERROR);
		result.index = i + 1;
		return (result);
	}
	len = get_operator_length(type);
	op[0] = input[i];
	op[1] = '\0';
	op[2] = '\0';
	if (len == 2)
		op[1] = input[i + 1];
	result.token = create_token(op, type);
	if (result.token)
		result.index = i + len;
	else
		result.index = i + len; // still move forward to avoid infinite loop
	return (result);
}

