#include "minishell.h"

void free_heredocs_in_command(t_command *command)
{
	t_heredoc *current;
	t_heredoc *next;

	if (!command)
		return;

	current = command->heredoc_head;
	while (current)
	{
		next = current->next;
		free(current->filename);
		free(current->delimiter);
		free(current);
		current = next;
	}

	command->heredoc_head = NULL; // Good practice to avoid dangling pointer
}

