#include "minishell.h"

static	int tokenize_and_expand(char *line, t_data *data, t_token **tokens)
{
	*tokens = lexer(data, line);
	if (!*tokens)
	{
		printf("Syntax error.\n");
		free_tokens(data);
		return (-1);
	}
	expand_token_values(*tokens, data);
	return (0);
}

static	int validate_and_parse(t_token *tokens, t_data *data, char *line)
{
	if (validate_syntax(tokens, data))
	{
		free_tokens(data);
		free(line);
		return (-1);
	}
	parse_commands(data, tokens);
	return (0);
}

static	int handle_heredocs(t_data *data, char *line)
{
	if (process_heredocs(data) == -1)
	{
		printf("======================== im here_04\n\n");
		free_tokens(data);
		free_commands(data);
		free(line);
		unlink_filename(data);
		return (-1);
	}
	return (0);
}

static	void execute_and_cleanup(t_data *data, char *line)
{
	execute_commands(data->command_head, data);
	unlink_filename(data);
	free_tokens(data);
	free_commands(data);
	free(line);
}

void	process_input(char *line, t_data *data)
{
	t_token *tokens = NULL;

	if (tokenize_and_expand(line, data, &tokens) == -1)
		return;
	if (validate_and_parse(tokens, data, line) == -1)
		return;
	if (handle_heredocs(data, line) == -1)
		return;
	execute_and_cleanup(data, line);
}
