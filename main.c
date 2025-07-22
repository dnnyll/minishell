/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
/*   Updated: 2025/07/17 11:40:05 by daniefe2         ###   ########.fr       */
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


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_data	data = init_data();
	data.environment_var = copy_environment(envp);
	// debug_environment_printer(&data);			//	test to print copy of environment as verification
	setup_parent_signals();
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
			continue ;
		}
		add_history(input_line);				//	adds action to history


		//	lexing % tokenizing
		
		t_token *tokens = lexer(&data, input_line);
		printf("calling lexer(&data, input_line) @ main.c\n");


		//	parsing
		printf("calling process_variables(input_line, &data, tokens) @ main.c\n");
		// process_variables(input_line, &data, tokens);
		expand_token_values(tokens, &data);		//	located in the folder tokens


		// validate_syntax(tokens);
		printf("calling validate_syntax(tokens) @ main.c\n");
		validate_syntax(tokens);

	//	separates words into tokens
		parse_commands(&data, tokens);
		// handle_pipes(&data, tokens, NULL);
		debug_parser_output(&data);
		execute_commands(data.command_head, &data);
		//free_char_array(data.environment_var);
		free_tokens(&data);						//	frees token list
		free_commands(&data);					//	frees command list
		free(input_line);						//	frees input line
	}
	
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
	free_char_array(data.environment_var);
	return (0);
}
