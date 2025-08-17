/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:32:49 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 15:41:47 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tokenize_and_expand(char *line, t_data *data, t_token **tokens)
{
	*tokens = lexer(data, line);
	if (!*tokens)
	{
		free_tokens(data);
		return (-1);
	}
	expand_token_values(*tokens, data);
	return (0);
}

static int	validate_and_parse(t_token *tokens, t_data *data, char *line)
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

static int	handle_heredocs(t_data *data, char *line)
{
	if (process_heredocs(data) == -1)
	{
		free_tokens(data);
		free_commands(data);
		free(line);
		unlink_filename(data);
		return (-1);
	}
	return (0);
}

static void	execute_and_cleanup(t_data *data, char *line)
{
	execute_commands(data->command_head, data);
	unlink_filename(data);
	free_tokens(data);
	free_commands(data);
	free(line);
}

void	process_input(char *line, t_data *data)
{
	t_token	*tokens;

	tokens = NULL;
	if (tokenize_and_expand(line, data, &tokens) == -1)
		return ;
	if (validate_and_parse(tokens, data, line) == -1)
		return ;
	if (handle_heredocs(data, line) == -1)
		return ;
	execute_and_cleanup(data, line);
}
