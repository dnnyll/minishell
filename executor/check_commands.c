/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:11:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/22 10:41:57 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_command *cmd)
{
	return (cmd && cmd->type == CMD);
}

int	is_redir(t_command *cmd)
{
	return (cmd && (cmd->type == REDIR_IN || cmd->type == REDIR_OUT
			|| cmd->type == APPEND || cmd->type == HEREDOC));
}

int	is_pipe(t_command *cmd)
{
	return (cmd && cmd->type == PIPE);
}
