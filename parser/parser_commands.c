#include "minishell.h"

/*
	information concerning: add_command_to_data

	purpose: adds a new command node to the end of the command list in the data structure.

	for: managing a linked list of commands parsed from the input.

	it:
	- checks if the command list is empty; if so, sets the new command as head
	- otherwise, traverses the list to the end and appends the new command node

	used to build the full list of parsed commands from the input line.
*/
void	add_command_to_data(t_command **head, t_command *init_command)
{
	// printf("add_command_to_data\n");
	// If the command list is empty, set the new command as the head of the list
	if (!*head)
	{
		*head = init_command;
		return ;
	}
	// Otherwise, find the last command in the list
	t_command *temp = *head;
	while (temp->next)			// Traverse until the last node (where next is NULL)
		temp = temp->next;
	// Append the new command at the end of the list
	temp->next = init_command;
}

/*
	information concerning: parse_segment_and_add_command

	purpose: parses a segment of tokens and stores it as a command in the data structure.

	for: parsing a part of the input between pipes (or the entire input if no pipes).

	it:
	- initializes a new command structure
	- fills it with data based on the token range (start, end)
	- adds the command to the global command list in data
	- increments the total command count

	this function handles the token logic for one command at a time.
*/
void	parse_segment_and_add_command(t_data *data, t_token *start, t_token *end)
{
	t_command *command = init_command();
	if (!command)
		return ; // Optionally handle error
	fill_command_segment(command, start, end);
	add_command_to_data(&data->command_head, command);
	data->command_count++;
}

/*
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
void	parse_commands(t_data *data, t_token *tokens)
{
	data->command_count = 0;
	data->pipe_count = 0;

	t_token *current = tokens;
	t_token *segment_start = current;

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

// void	parse_commands(t_data *data, t_token *tokens)
// {
// 	// printf("parse_commands\n");
// 	data->command_count = 0;
// 	data->pipe_count = 0;
// 	t_token	*current = tokens;
// 	t_token	*segment_start = current;
// 	while (current)
// 	{
// 		if (current->type == PIPE)
// 		{
// 			data->pipe_count++;
// 			// Cut the segment here
// 			current->type = PIPE;  // Optional: mark the pipe visually
// 			// Parse the segment [segment_start ... current (exclusive)]
// 			t_command *command = init_command();
// 			if (!command)
// 				return ; // handle error
// 			// command->redir_head = data->redir_head;
// 			fill_command_segment(command, segment_start, current); // You'll write this
// 			add_command_to_data(&data->command_head, command);
// 			data->command_count++;
// 			segment_start = current->next; // move to next segment
// 		}
// 		current = current->next;
// 	}
// 	//printf("After loop, segment_start = %p\n", (void *)segment_start);
// 	// Handle the final segment (after last pipe or if no pipes)
// 	if (segment_start)
// 	{
// 		//printf("Initiating segment_start condition\n");
// 		t_command *command = init_command();
// 		if (!command)
// 		{
// 			printf("Failed to allocate new_command\n");
// 			return ; // handle error
// 		}
// 		// command->redir_head = data->redir_head;
// 		fill_command_segment(command, segment_start, NULL);
// 		add_command_to_data(&data->command_head, command);
// 		data->command_count++;
// 		//printf("Added final command\n");
// 	}
// }
