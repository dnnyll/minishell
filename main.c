/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/06 13:41:55 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirects(t_redirect *redir)
{
	t_redirect *next;

	while (redir)
	{
		next = redir->next;
		free(redir->file);
		redir->file = NULL;
		free(redir);
		redir = next;
	}
}


static void	free_tokens(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}
// Free a linked list of command structs and all their dynamic fields
static void	free_commands(t_command *cmd)
{
	t_command *next;
	int i;

	while (cmd)
	{
		next = cmd->next;

		// Free each string in argv array if it exists
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			free(cmd->argv[i]); // Assumes each string was ft_strdup'ed
			i++;
		}
		free(cmd->argv); // Free the argv array itself

		// Free input redirections list
		free_redirects(cmd->redir_in);

		// Free output redirections list
		free_redirects(cmd->redir_out);

		// Free the command struct
		free(cmd);

		// Move to next command in the pipeline
		cmd = next;
	}
}



const char *token_type_str(t_token_type type)
{
	if (type == WORD) return "WORD";
	if (type == PIPE) return "PIPE";
	if (type == REDIR_IN) return "REDIR_IN";
	if (type == REDIR_OUT) return "REDIR_OUT";
	if (type == HEREDOC) return "HEREDOC";
	if (type == APPEND) return "APPEND";
	if (type == T_EOF) return "EOF";
	if (type == ERROR) return "ERROR";
	if (type == ENV) return "ENV";
	return ("UNKNOWN");
}

const char *quote_type_str(t_quote_type quote)
{
	if (quote == NO_QUOTE) return "None";
	if (quote == SINGLE_QUOTE) return "Single";
	if (quote == DOUBLE_QUOTE) return "Double";
	return ("Unknown");
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char	*input_line;

	while (1)
	{
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
		t_token *tokens = lexer(input_line);	//	separates words into tokens
		t_command *cmds = parse_tokens(tokens);
		print_commands(cmds);
		free_commands(cmds);
		print_tokens(tokens);					//	prints tokens types
		free_tokens(tokens);					//	frees token list
		free(input_line);						//	frees input line
	}
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
}