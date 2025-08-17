/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:31:23 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:31:24 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_segment(t_data *data, t_token *start, t_token *end)
{
	t_command	*cmd;

	cmd = init_command();
	if (!cmd)
		return (perror("Error: malloc sizeof t_command @"
				"parser_pipes_handling.c\n"));
	fill_command_segment(cmd, start, end);
	add_command_to_data(&data->command_head, cmd);
}

void	handle_pipes(t_data *data, t_token *start, t_token *end)
{
	t_token		*segment_start;
	t_token		*current;

	segment_start = start;
	current = start;
	while (current && current != end)
	{
		if (current->type == PIPE)
		{
			data->pipe_count++;
			add_segment(data, segment_start, current);
			segment_start = current->next;
		}
		current = current->next;
	}
	if (segment_start && segment_start != end)
		add_segment(data, segment_start, end);
}
