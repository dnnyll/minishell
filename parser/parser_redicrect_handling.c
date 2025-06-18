/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redicrect_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:25:11 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/18 13:45:30 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(int type)
{
	return (type == REDIR_IN || type == REDIR_OUT 
			|| type == APPEND || type == HEREDOC);
}

/*
	information concerning: handle_redirections

	purpose: parses and stores redirection information inside the command structure.

	for: echo hello > file.txt

	it detects redirection tokens (e.g. >, >>, <, <<) and saves the corresponding 
	filenames or delimiters into the command structure.

	- infile: for '<'
	- outfile: for '>' and '>>'
	- append: 0 for '>', 1 for '>>'
	- heredoc_delim: for '<<'

	without this, the shell wouldn’t know which files to open for input/output 
	before calling execve().
	it loops from start to end tokens, only handling redirections.
*/

void	handle_redirections(t_command *command, t_token *start, t_token *end)
{
	printf("handle_redirections\n");
	t_token *current = start;
	
	while (current && current != end)
	{
		if (current->type == REDIR_IN && current->next && current->next->type == WORD)
		{
			command->infile = ft_strdup(current->next->value);
			current = current->next;
		}
		else if (current->type == REDIR_OUT && current->next && current->next->type == WORD)
		{
			command->outfile = ft_strdup(current->next->value);
			command->append = 0;
			current = current->next;
		}
		else if (current->type == APPEND && current->next && current->next->type == WORD)
		{
			command->outfile = ft_strdup(current->next->value);
			command->append = 1;
			current = current->next;
		}
		else if (current->type == HEREDOC && current->next && current->next->type == WORD)
		{
			command->heredoc_delim = ft_strdup(current->value);
			current = current->next;
		}
		current = current->next;
	}
}