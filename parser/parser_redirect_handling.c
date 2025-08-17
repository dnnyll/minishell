/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:31:27 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:54:57 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

static void	set_redir_in(t_command *command, t_token *current)
{
	if (command->infile)
		free(command->infile);
	command->infile = ft_strdup(current->next->value);
}

static void	set_redir_out(t_command *command, t_token *current, int append)
{
	if (command->outfile)
		free(command->outfile);
	command->outfile = ft_strdup(current->next->value);
	command->append = append;
}

static void	set_heredoc(t_command *cmd, t_token *current)
{
	t_heredoc	*new;
	t_heredoc	*tmp;

	new = init_heredoc(cmd->heredoc_count);
	if (!new)
		return ;
	new->delimiter = ft_strdup(current->next->value);
	new->quoted = (current->next->quote != NO_QUOTE);
	if (!cmd->heredoc_head)
		cmd->heredoc_head = new;
	else
	{
		tmp = cmd->heredoc_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_redirections(t_command *command, t_token *start, t_token *end)
{
	t_token	*current;

	current = start;
	command->heredoc_count = 0;
	while (current && current != end)
	{
		if (current->next && current->next->type == WORD)
		{
			if (current->type == REDIR_IN)
				set_redir_in(command, current);
			else if (current->type == REDIR_OUT)
				set_redir_out(command, current, 0);
			else if (current->type == APPEND)
				set_redir_out(command, current, 1);
			else if (current->type == HEREDOC)
			{
				command->heredoc_count++;
				set_heredoc(command, current);
			}
			current = current->next;
		}
		current = current->next;
	}
}
