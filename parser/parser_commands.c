#include "minishell.h"

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

void	parse_commands(t_data *data, t_token *tokens)
{
	// printf("parse_commands\n");
	data->command_count = 0;
	data->pipe_count = 0;
	t_token	*current = tokens;
	t_token	*segment_start = current;
	while (current)
	{
		if (current->type == PIPE)
		{
			data->pipe_count++;
			// Cut the segment here
			current->type = PIPE;  // Optional: mark the pipe visually
			// Parse the segment [segment_start ... current (exclusive)]
			t_command *command = init_command();
			if (!command)
				return ; // handle error
			command->redir_head = data->redir_head;
			fill_command_segment(command, segment_start, current); // You'll write this
			add_command_to_data(&data->command_head, command);
			data->command_count++;
			segment_start = current->next; // move to next segment
		}
		current = current->next;
	}
	//printf("After loop, segment_start = %p\n", (void *)segment_start);
	// Handle the final segment (after last pipe or if no pipes)
	if (segment_start)
	{
		//printf("Initiating segment_start condition\n");
		t_command *command = init_command();
		if (!command)
		{
			printf("Failed to allocate new_command\n");
			return ; // handle error
		}
		command->redir_head = data->redir_head;
		fill_command_segment(command, segment_start, NULL);
		add_command_to_data(&data->command_head, command);
		data->command_count++;
		//printf("Added final command\n");
	}
}
