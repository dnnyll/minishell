/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:31:13 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:31:14 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command_to_data(t_command **head, t_command *init_command)
{
	t_command	*temp;

	if (!*head)
	{
		*head = init_command;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = init_command;
}

void	parse_segment_and_add_command(t_data *data, t_token *start,
			t_token *end)
{
	t_command	*command;

	command = init_command();
	if (!command)
		return ;
	fill_command_segment(command, start, end);
	add_command_to_data(&data->command_head, command);
	data->command_count++;
}

void	parse_commands(t_data *data, t_token *tokens)
{
	t_token	*current;
	t_token	*segment_start;

	current = tokens;
	segment_start = current;
	data->command_count = 0;
	data->pipe_count = 0;
	while (current)
	{
		if (current->type == PIPE)
		{
			data->pipe_count++;
			parse_segment_and_add_command(data, segment_start, current);
			segment_start = current->next;
		}
		current = current->next;
	}
	if (segment_start)
		parse_segment_and_add_command(data, segment_start, NULL);
}

/*
	information concerning: add_command_to_data

	purpose: adds a new command node to the end of the command list
		in the data structure.

	for: managing a linked list of commands parsed from the input.

	it:
	- checks if the command list is empty; if so, sets the new command as head
	- otherwise, traverses the list to the end and appends the new command node

	used to build the full list of parsed commands from the input line.

	information concerning: parse_segment_and_add_command

	purpose: parses a segment of tokens and stores it as a command
		in the data structure.

	for: parsing a part of the input between pipes (or the entire
		input if no pipes).

	it:
	- initializes a new command structure
	- fills it with data based on the token range (start, end)
	- adds the command to the global command list in data
	- increments the total command count

	this function handles the token logic for one command at a time.
	
	information concerning: parse_commands

	purpose: splits the token list into separate commands and parses each one.

	for: an input like "ls -l | grep .c | wc -l"

	it:
	- initializes command and pipe counters
	- walks through the list of tokens
	- on encountering a PIPE token, treats the tokens before it as one command
	- parses each command segment and adds it to the command list
	- finally, parses the last segment after the last pipe

	this function breaks the full token list into manageable command segments.
*/