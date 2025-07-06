/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
/*   Updated: 2025/07/06 17:18:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Frees a linked list of redirection structs
// static void	free_redirects(t_redirect *redir)
// {
// 	t_redirect *next;

// 	while (redir)
// 	{
// 		next = redir->next;
// 		free(redir->file);
// 		free(redir);
// 		redir = next;
// 	}
// }

// Frees all tokens from data->token_head
void	free_tokens(t_data *data)
{
	t_token	*token = data->token_head;
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
	data->token_head = NULL; // Clear reference in data
}

// Frees all commands from data->cmd_head
// void	free_commands(t_data *data)
// {
// 	t_command *cmd = data->command_head;
// 	t_command *next;
// 	int i;

// 	while (cmd)
// 	{
// 		next = cmd->next;

// 		if (cmd->argv)
// 		{
// 			i = 0;
// 			while (cmd->argv[i])
// 				free(cmd->argv[i++]);
// 			free(cmd->argv);
// 		}

// 		free_redirects(cmd->redir_in);
// 		free_redirects(cmd->redir_out);

// 		free(cmd);
// 		cmd = next;
// 	}
// 	data->command_head = NULL; // Clear reference in data
// }

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_data	data = init_data();
	data.environment_variables = copy_environment(envp);
	// debug_environment_printer(&data);			//	test to print copy of environment as verification
	char	*input_line;


	//	test to search and print $HOME
	// get_env_value(&data, "HOME");

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
			continue;
		}
		add_history(input_line);				//	adds action to history


		//	lexing % tokenizing
		t_token *tokens = lexer(&data, input_line);



		//	parsing
		printf("main: process_variables(input_line, &data, tokens)\n");
		// process_variables(input_line, &data, tokens);
		expand_token_values(tokens, &data);		//	located in the folder tokens


		// validate_syntax(tokens);
		printf("main: validate_syntax(tokens)\n");
		validate_syntax(tokens);





		//	executing.
		
		// Update exit_status from the result of this execution
		//	- data->exit_status = get_exit_status();	this is necessary for the function expand_variable


		
		// simple check to verify lexer output
		// if (!tokens)
		// 	printf("Lexer returned NULL tokens\n");
		// else
		// {
		// 	printf("Lexer returned tokens:\n");
		// 	t_token *tmp = tokens;
		// 	while (tmp)
		// 	{
		// 		printf("Value: %-20s | Type: %d | Quote: %d\n", tmp->value, tmp->type, tmp->quote);
		// 		tmp = tmp->next;
		// 	}
		// }


		
	//	separates words into tokens
		parse_commands(&data, tokens);
		// handle_pipes(&data, tokens, NULL);
		debug_parser_output(&data);
		// print_commands(data.command_head);
		// print_commands(&data);
		// free_commands(&data);
		// print_tokens(&data);					//	prints tokens types
		printf("pipe count = %d\n", data.pipe_count);
		free_char_array(data.environment_variables);
		free_tokens(&data);						//	frees token list
		free_commands(&data);					//	frees command list
		free(input_line);						//	frees input line
	}
	
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
}