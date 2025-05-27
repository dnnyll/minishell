/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:26:04 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/27 07:05:02 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-15s | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
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
			exit(1);
		}
		if (input_line[0] == '\0')				// trigers when enter is pressed on a empty line
		{
			free(input_line);
			continue;
		}
		add_history(input_line);				//	adds action to history
		t_token *tokens = lexer(input_line);	//	separates words into tokens
		print_tokens(tokens);
	}
}