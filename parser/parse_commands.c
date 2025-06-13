/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/13 11:05:15 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int count_nodes(t_token *head)
// {
// 	int count = 0;
// 	t_token *temp = head;	//“Give me the address of the first node in your token list, and I’ll walk through the list using the next pointers.”

// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == WORD)
// 			count++;
// 		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
// 			|| temp->type == APPEND || temp->type == HEREDOC)
// 			temp = temp->next; // skip redirection target
// 		temp = temp->next;
// 	}
// 	return (count);
// }


// char **argument_collect(t_token *head)
// {
// 	int size = count_nodes(head);
// 	char **argv = malloc(sizeof(char *) * (size + 1));
// 	if (!argv)
// 		return (NULL);
// 	return argument_fill(argv, head);
// }

// char **argument_fill(char **argv, t_token *head)
// {
// 	t_token *temp = head;
// 	int i = 0;

// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == WORD)
// 		{
// 			argv[i++] = ft_strdup(temp->value);
// 			temp = temp->next;
// 		}
// 		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
// 			|| temp->type == APPEND || temp->type == HEREDOC)
// 		{
// 			temp = temp->next; // skip file token
// 			if (temp)
// 				temp = temp->next;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// 	argv[i] = NULL;
// 	return argv;
// }

// char **argument_collect(t_token *head)
// {
// 	char	**argv;
// 	int	size = count_nodes(head);
// 	argv = alloc_argv(NULL, size);
// 	if (!argv)
// 		return (NULL);
// 	argument_fill(argv, head);
// 	return (argv);
// }

t_command	*new_command(void)
{
	printf("new_command\n");
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->heredoc_delim = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->append = 0;
	command->is_builtin = 0;
	command->next = NULL;
	return (command);
}
/*
	purpose:	this function is responsible for inserting a new t_command structure
				(which represents one full parsed command segment) into the linked list of commands.
				This list is stored in t_data->command_head (or simply head when passed to the function).

				It maintains the ordered list of parsed commands.
				It ensures that each new parsed command is properly appended to the end of the list.
				It allows the parser to build the full pipeline of commands, one by one.
*/
void	add_command_to_data(t_command **head, t_command *new_command)
{
	printf("add_command_to_data\n");
	// If the command list is empty, set the new command as the head of the list
	if (!*head)
	{
		*head = new_command;
		return ;
	}
	// Otherwise, find the last command in the list
	t_command *temp = *head;
	while (temp->next)			// Traverse until the last node (where next is NULL)
		temp = temp->next;
	// Append the new command at the end of the list
	temp->next = new_command;
}

void	parse_commands(t_data *data, t_token *tokens)
{
	printf("parse_commands\n");
	t_token	*current = tokens;
	t_token	*segment_start = current;
	printf("0\n");
	while (current)
	{
		printf("1\n");
		if (current->type == PIPE)
		{
			printf("2\n");
			// Cut the segment here
			current->type = T_EOF;  // Optional: mark the pipe visually
			// Parse the segment [segment_start ... current (exclusive)]
			t_command *command = new_command();
			if (!command)
				return ; // handle error
			fill_command_segment(command, segment_start, current); // You'll write this
			add_command_to_data(&data->command_head, command);
			segment_start = current->next; // move to next segment
		}
		current = current->next;
	}
	printf("After loop, segment_start = %p\n", (void *)segment_start);
	// Handle the final segment (after last pipe or if no pipes)
	if (segment_start)
	{
		printf("Initiatin segment_start condition\n");
		t_command *command = new_command();
		if (!command)
		{
			printf("Failed to allocate new_command\n");
			return ; // handle error
		}
		fill_command_segment(command, segment_start, NULL);
		add_command_to_data(&data->command_head, command);
		printf("Added final command\n");
	}
}
