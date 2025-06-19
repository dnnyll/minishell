/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2025/06/09 11:35:34 by mrosset          ###   ########.fr       */
=======
/*   Updated: 2025/06/18 10:53:03 by daniefe2         ###   ########.fr       */
>>>>>>> feature-daniefe2-parser
=======
/*   Updated: 2025/06/19 14:25:22 by daniefe2         ###   ########.fr       */
>>>>>>> feature-daniefe2-parser
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
	data.environment = copy_environment(envp);
	debug_environment_printer(&data);
	char	*input_line;
	
	get_env_value(&data, "HOME");
	while (1)
	{
		setup_parent_signals();					// shell signal handling
		input_line = readline(PROMPT);			//	displays prompt
		if (input_line == NULL)					//	trigers when ctrl + D is used
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
		t_token *tokens = lexer(&data, input_line);

		//	parsing
		//	executing
		// Update exit_status from the result of this execution
		//	- data->exit_status = get_exit_status();	this is necessary for the function expand_variable

		// simple check to verify lexer output
		if (!tokens)
			printf("Lexer returned NULL tokens\n");
		else
		{
			printf("Lexer returned tokens:\n");
			t_token *tmp = tokens;
			while (tmp)
			{
				printf("Value: %-20s | Type: %d | Quote: %d\n", tmp->value, tmp->type, tmp->quote);
				tmp = tmp->next;
			}
		}


		
	//	separates words into tokens
		parse_commands(&data, tokens);
		// handle_pipes(&data, tokens, NULL);
		debug_parser_output(&data);
		// print_commands(data.command_head);
		// print_commands(&data);
		// free_commands(&data);
		// print_tokens(&data);					//	prints tokens types
		printf("pipe count = %d\n", data.pipe_count);
		free_char_array(data.environment);
		free_tokens(&data);						//	frees token list
		free_commands(&data);					//	frees command list
		free(input_line);						//	frees input line
	}
	
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
}