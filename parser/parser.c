/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:33:26 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/06 13:47:17 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create and return a new command node
static	t_command *create_new_command_node(void)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = NULL;
	command->redir_in = NULL;
	command->redir_out = NULL;
	command->next = NULL;
	return (command);
}

// Parse a full list of tokens into a linked list of commands

t_command	*parse_tokens(t_token *token_list)
{
	t_command	*command_list = NULL;
	t_command	*last_command = NULL;
	t_token *current = token_list;

	while (current)
	{
		// Create a new command node
		t_command	*command = create_new_command_node();
		if (!command)
			return (NULL);
		// Parse arguments (e.g. command name + args) from this segment
		command->argv = argument_collect(current);
		// Detect redirections and attach to cmd->redir_in / cmd->redir_out
		detect_redirections(current, command);
		// Append to the command list
		if (!command_list)
			command_list = command;
		else
			last_command->next = command;
		last_command = command;
		// Move current to the next command segment after a PIPE
		while (current && current->type != PIPE)
			current = current->next;
		if (current && current->type == PIPE)
			current = current->next;
	}
	return (command_list);
}
