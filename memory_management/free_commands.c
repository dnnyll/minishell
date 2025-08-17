/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:30:20 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:30:22 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_node(t_command *cmd)
{
	free_heredocs_in_command(cmd);
	free_char_array(cmd->argv);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd->path);
	free(cmd->value);
	free(cmd);
}

void	*get_next_command(void *node)
{
	return (((t_command *)node)->next);
}

void	free_commands(t_data *data)
{
	free_list(data->command_head, get_next_command,
		(void (*)(void *))free_command_node);
	data->command_head = NULL;
}
