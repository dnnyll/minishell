#include "minishell.h"

t_command	*new_command(void)
{
	// printf("new_command\n");
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

void	add_command_to_data(t_command **head, t_command *new_command)
{
	// printf("add_command_to_data\n");
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
	// printf("parse_commands\n");
	t_token	*current = tokens;
	t_token	*segment_start = current;
	while (current)
	{
		if (current->type == PIPE)
		{
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
