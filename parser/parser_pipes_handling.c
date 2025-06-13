/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipes_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:20:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/13 16:38:12 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipes(t_command *command, t_token *start, t_token *end)
{
	t_token *current = start;
	
	while (current && current != end)
	{
		if (current->type == PIPE && current->next && current->next->type == WORD)
		{
			comannd_
		}
	}
}
