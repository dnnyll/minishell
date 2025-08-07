#include "minishell.h"

void free_heredoc_list(t_heredoc *heredoc)
{
	t_heredoc *next;

	while (heredoc)
	{
		next = heredoc->next;
		free(heredoc->filename);
		free(heredoc->delimiter);
		free(heredoc);
		heredoc = next;
	}
}
