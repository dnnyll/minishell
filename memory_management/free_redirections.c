#include "minishell.h"

void	free_redir_list(t_redir *head)
{
	t_redir	*current;

	while (head)
	{
		current = head->next;
		free(head->filename);
		free(head);
		head = current;
	}
}
