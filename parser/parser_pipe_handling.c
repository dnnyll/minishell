#include "minishell.h"


static void	add_segment(t_data *data, t_token *start, t_token *end)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (perror("Error: malloc sizeof t_command @"
				"parser_pipes_handling.c\n"));
	fill_command_segment(cmd, start, end);
	add_command_to_data(&data->command_head, cmd);
}

void	handle_pipes(t_data *data, t_token *start, t_token *end)
{
	t_token		*segment_start;
	t_token		*current;

	segment_start = start;
	current = start;
	while (current && current != end)
	{
		if (current->type == PIPE)
		{
			data->pipe_count++;
			add_segment(data, segment_start, current);
			segment_start = current->next;
		}
		current = current->next;
	}
	if (segment_start && segment_start != end)
		add_segment(data, segment_start, end);
}

// void	handle_pipes(t_data *data, t_token *start, t_token *end)
// {
// 	t_token		*segment_start = start;
// 	t_token		*current = start;
// 	t_command	*new_pipe_command;
// 	while (current && current != end)
// 	{
// 		if (current->type == PIPE)
// 		{
// 			data->pipe_count++;
// 			new_pipe_command = init_command();
// 			if (!new_pipe_command)
// 			return (perror("Error: malloc sizeof t_command @"
//				"parser_piepes_handling.c\n"));
// 			fill_command_segment(new_pipe_command, segment_start, current);
// 			add_command_to_data(&data->command_head, new_pipe_command);
// 			segment_start = current->next;
// 		}
// 		current = current->next;
// 	}
// 	if (segment_start && segment_start != end)
// 	{
// 		new_pipe_command = init_command();
// 		if (!new_pipe_command)
// 			return(perror("Error: initi new_command @ handle_pipes\n"));
// 		fill_command_segment(new_pipe_command, segment_start, end);
// 		add_command_to_data(&data->command_head, new_pipe_command);
// 	}
// }