#include "minishell.h"

t_data	*initialize_minishell(char **envp)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	data->environment_var = copy_environment(envp);
	data->env_head = build_env_list(data->environment_var);
	return (data);
}

void	handle_exit(t_data *data)
{
	printf("@handle_exit\n\n");
	// (void)data;
	printf("exit\n");
	clear_history();
	rl_clear_history();
	free_data_list(&data);

	// debug_parser_output(data);
}

bool	should_skip_line(char *line)
{
	// if (g_signal_status == SIGINT)
	// {
	// 	g_signal_status = 0;
	// 	free(line);
	// 	return (true);
	// }
	if (line[0] == '\0')
	{
		free(line);
		return (true);
	}
	add_history(line);
	return (false);
}

void	process_input(char *line, t_data *data)
{
	printf("@process_input\n\n");
	t_token	*tokens;

	tokens = lexer(data, line);
	if(!tokens)
	{
		printf("Lexer returned NULL — likely due to unmatched quotes or syntax error.\n");
		return ;
	}
	expand_token_values(tokens, data);
	// print_tokens(data);
	//print_tokens(data);
	if (validate_syntax(tokens, data))
		return (free_tokens(data), free(line));
	parse_commands(data, tokens);
	// printf("print_heredoc_01\n");
	// print_heredoc(data->command_head);
	// debug_parser_output(data);
	if (process_heredocs(data) == -1)
	{
		printf("@process_heredocs failure\n\n");
		free_tokens(data);
		free_commands(data);
		free (line);
		return ;
	}
	printf("after: process_heredocs(data) == -1\n\n");
	// execute_commands(data->command_head, data);
	// free_data_list(data);
	// free_heredocs_in_command(data->command_head);
	// printf("print_heredoc_02\n");
	// print_heredoc(data->command_head);
	free_tokens(data);
	free_commands(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input_line;

	(void)argc;
	(void)argv;
	data = initialize_minishell(envp);
	if (!data)
		return (1);
	setup_parent_signals();
	while (1)
	{
		input_line = readline("minishell> ");
		if (!input_line)
			return (handle_exit(data), 0);
		if (should_skip_line(input_line))
			continue ;
		process_input(input_line, data);
	}
	return (0);
}
