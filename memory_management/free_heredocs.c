/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:30:54 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:30:56 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredocs_in_command(t_command *command)
{
	t_heredoc	*current;
	t_heredoc	*next;

	if (!command)
		return ;
	current = command->heredoc_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->filename);
		free(current->delimiter);
		free(current);
		current = next;
	}
	command->heredoc_head = NULL;
}
