/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:11:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/03 15:07:38 by mrosset          ###   ########.fr       */
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

void	child_exit_code(int status, t_data *data)
{
	int	sig;

	if (WIFEXITED(status))
		data->last_exit_code_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		data->last_exit_code_status = 128 + sig;
	}
}

void	print_error(char *prefix, char *arg, char *suffix)
{
	if (prefix)
		ft_putstr_fd(prefix, 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	if (suffix)
		ft_putstr_fd(suffix, 2);
}
