#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_data	*data = init_data();
	data->redir_head = init_redir();
		if (!data->redir_head)
			return (printf("REDIT INIT IN MAIN IS FUCKING UP\n"), 1); 
	data->environment_var = copy_environment(envp);
	data->env_head = build_env_list(data->environment_var);
	// debug_environment_printer(data);			//	test to print copy of environment as verification
	setup_parent_signals();
	char	*input_line;

	while (1)
	{
		input_line = readline("minishell> ");
		if (!input_line)
		{
			printf("exit\n");
			break ;
		}
		if (input_line[0] == '\0')				// trigers when enter is pressed on a empty line
		{
			free(input_line);
			continue ;
		}
		add_history(input_line);				//	adds action to history


		//	lexing % tokenizing
		
		t_token *tokens = lexer(data, input_line);
		printf("calling lexer(data, input_line) @ main.c\n");


		//	parsing
		printf("calling process_variables(input_line, data, tokens) @ main.c\n");
		// process_variables(input_line, data, tokens);
		expand_token_values(tokens, data);		//	located in the folder tokens


		// validate_syntax(tokens);
		printf("calling validate_syntax(tokens) @ main.c\n");
		validate_syntax(tokens);

		//	separates words into tokens
		parse_commands(data, tokens);

		//	hadnle heredocs in the limbo phase
		// launch_heredoc(data);
		if (process_heredocs(data) == -1)
		{
			perror("heredoc");
			// clean up and return
		}
		// handle_pipes(data, tokens, NULL);
		debug_parser_output(data);
		execute_commands(data->command_head, data);
		//free_char_array(data->environment_var);
		free_tokens(data);						//	frees token list
		free_commands(data);					//	frees command list
		free(input_line);						//	frees input line
	}
	
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
	free_char_array(data->environment_var);
	return (0);
}
