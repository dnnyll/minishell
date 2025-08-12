#include "minishell.h"

t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

static int	verify_pipe_sequence(t_token *tokens, t_data *data)
{
	t_token	*current;

	current = tokens;
	if (current->type == PIPE && current->next->type == PIPE)
		return (print_error("minishell: syntax error near unexpected"
				"token `|'\n", NULL, NULL),
			data->last_exit_code_status = 2, 1);
	if (current->type == PIPE
		&& (current->next->type == REDIR_IN
			|| current->next->type == REDIR_OUT
			|| current->next->type == HEREDOC
			|| current->next->type == APPEND))
	{
		if (!current->next->next || current->next->next->type != WORD)
			return (print_error("minishell: syntax error near unexpected"
					"token`newline'\n", NULL, NULL),
				data->last_exit_code_status = 2, 1);
		if (access(current->next->next->value, F_OK) != 0)
			return (print_error("minishell: ", current->next->next->value,
					": No such file or directory\n"),
				data->last_exit_code_status = 1, 1);
	}
	return (0);
}

int	verify_pipes(t_token *tokens, t_data *data)
{
	t_token	*current;

	if (!tokens)
		return (data->last_exit_code_status = 2, 1);
	if (tokens->type == PIPE)
		return (print_error("minishell: syntax error near unexpected token"
				"`|'\n", NULL, NULL), data->last_exit_code_status = 2, 1);
	current = tokens;
	while (current && current->next)
	{
		if (verify_pipe_sequence(current, data))
			return (1);
		current = current->next;
	}
	if (current->type == PIPE)
		return (print_error("minishell: syntax error near unexpected token"
				"`|'\n", NULL, NULL), data->last_exit_code_status = 2, 1);
	return (0);
}

int	verify_redirections(t_token *tokens, t_data	*data)
{
	t_token		*current;

	current = tokens;
	if (!current)
		return (1);
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!current->next)
			{
				data->last_exit_code_status = 2;
				print_error("minishell: syntax error near unexpected token"
					"`newline'\n", NULL, NULL);
				return (1);
			}
			if (current->next->type != WORD)
				return (print_error("syntax error near unexpected token"
						"`newline'\n", NULL, NULL), 1);
		}
		current = current->next;
	}
	return (0);
}

int	validate_syntax(t_token *tokens, t_data *data)
{
	t_token	*last_token;

	if (!tokens)
		return (data->last_exit_code_status = 2,
			printf("Error: no tokens @ validate_syntax\n"), 1);
	last_token = get_last_token(tokens);
	if (tokens->type == PIPE || last_token->type == PIPE)
		return (print_error("minishell: syntax error near unexpected token"
				"`|'\n", NULL, NULL), data->last_exit_code_status = 2, 1);
	if (verify_pipes(tokens, data))
		return (1);
	if (verify_redirections(tokens, data))
		return (1);
	return (0);
}
