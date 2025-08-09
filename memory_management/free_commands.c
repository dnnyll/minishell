#include "minishell.h"

void	free_command_node(t_command *cmd)
{
	free_char_array(cmd->argv);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->path);
	free(cmd->value);
	free(cmd);
}

void	*get_next_command(void *node)
{
	return ((t_command *)node)->next;
}

void	free_commands(t_data *data)
{
	free_list(data->command_head, get_next_command, (void (*)(void *))free_command_node);
	data->command_head = NULL;
}


// void	free_commands(t_data *data)
// {
// 	t_command *current = data->command_head;
// 	t_command *next;

// 	while (current)
// 	{
// 		next = current->next;
// 		free_command_fields(current);
// 		free(current);
// 		current = next;
// 	}
// 	data->command_head = NULL;
// }