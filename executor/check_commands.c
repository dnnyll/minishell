/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:11:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/03 13:46:23 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_cmd *cmd)
{
	return (cmd && cmd->type == CMD);
}

int	is_redirection(t_cmd *cmd)
{
	return (cmd && (cmd->type == REDIR_IN || cmd->type == REDIR_OUT
			|| cmd->type == APPEND || cmd->type == HEREDOC));
}

int	is_pipe(t_cmd *cmd)
{
	return (cmd && cmd->type == PIPE);
}
