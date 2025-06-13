/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 10:33:26 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/12 11:35:36 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// // Create and return a new command node
// static	t_command *create_new_command_node(void)
// {
// 	t_command *command;

// 	command = malloc(sizeof(t_command));
// 	if (!command)
// 		return (NULL);
// 	command->argv = NULL;
// 	command->redir_in = NULL;
// 	command->redir_out = NULL;
// 	command->next = NULL;
// 	return (command);
// }

// Parse a full list of tokens into a linked list of commands

// t_command *parse_tokens(t_token *token_list)
// {
// 	t_command *command_list = NULL;
// 	t_command *last_command = NULL;
// 	t_token *current = token_list;

// 	while (current)
// 	{
// 		t_command *cmd = create_new_command_node();
// 		if (!cmd)
// 			return (NULL);

// 		cmd->argv = argument_collect(&current);
// 		current = detect_redirections(current, cmd);

// 		if (cmd->argv && cmd->argv[0]) // only keep valid commands
// 		{
// 			if (!command_list)
// 				command_list = cmd;
// 			else
// 				last_command->next = cmd;
// 			last_command = cmd;
// 		}
// 		else
// 			free_command(cmd); // free unused command

// 		if (current && current->type == PIPE)
// 			current = current->next;
// 	}
// 	return (command_list);
// }

