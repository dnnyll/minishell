/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:12:11 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/07 13:30:43 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_single_builtin(t_command *cmd, t_data *data)
{
	int	std_in;
	int	std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (edit_pipe_fd(cmd, -1, (int [2]){-1, -1}, data) != 0)
	{
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		close(std_in);
		close(std_out);
		return ;
	}
	execute_buitlins(cmd, data);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
}

void	wait_for_child(pid_t last_pid, t_data *data)
{
	int		status;
	pid_t	pid;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				data->last_exit_code_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->last_exit_code_status = 128 + WTERMSIG(status);
		}
	}
}
