/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/31 10:27:51 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static const char *token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD) return "WORD";
	if (type == TOKEN_PIPE) return "PIPE";
	if (type == TOKEN_REDIR_IN) return "REDIR_IN";
	if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
	if (type == TOKEN_HEREDOC) return "HEREDOC";
	if (type == TOKEN_APPEND) return "APPEND";
	if (type == TOKEN_EOF) return "EOF";
	if (type == TOKEN_ERROR) return "ERROR";
	if (type == TOKEN_ENV) return "ENV";
	return "UNKNOWN";
}

static const char *quote_type_str(t_quote_type quote)
{
	if (quote == NO_QUOTE) return "None";
	if (quote == SINGLE_QUOTE) return "Single";
	if (quote == DOUBLE_QUOTE) return "Double";
	return "Unknown";
}

void print_tokens(t_token *tokens)
{
	printf("\n--- Token List ---\n");
	while (tokens)
	{
		printf("Value: %-20s | Type: %-10s | Quote: %s\n",
			tokens->value,
			token_type_str(tokens->type),
			quote_type_str(tokens->quote));
		tokens = tokens->next;
	}
	printf("-------------------\n\n");
}


void	free_tokens(t_token *tokens)
{
	t_token *temp;

	while (tokens)
	{
		temp = tokens->next;
		free (tokens->value);
		free (tokens);
		tokens = temp;
	}
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
		print_tokens(tokens);					//	prints tokens types
		free_tokens(tokens);					//	frees token list
		free(input_line);						//	frees input line
	}
	clear_history();							//	frees history list
	rl_clear_history();							//	cleans up internal readline history structures
}