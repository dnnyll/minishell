#include "minishell.h"

void	free_string(char **str)
{
	int	i = 0;
	if (!str)
		return;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_command_fields(t_command *cmd)
{
	free_string(cmd->argv);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->path);
	free(cmd->value);
	free(cmd->heredoc_delim);
	// Assuming heredoc_count is now an int, no need to free.
}

void	free_commands(t_data *data)
{
	t_command *current = data->command_head;
	t_command *next;

	while (current)
	{
		next = current->next;
		free_command_fields(current);
		free(current);
		current = next;
	}
	data->command_head = NULL;
}