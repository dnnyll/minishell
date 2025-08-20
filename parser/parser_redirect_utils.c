#include "minishell.h"

int	is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

t_redir	*new_redir(const char *filename, bool append)
{
	t_redir *node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->filename = ft_strdup(filename);
	node->append = append;
	node->next = NULL;
	return (node);
}

void	add_redir(t_redir **head, t_redir *new)
{
	t_redir *tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

