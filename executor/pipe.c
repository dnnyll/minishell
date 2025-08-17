/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:47:47 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/17 10:47:50 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_command *cmd, int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
	if (cmd && cmd->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe error");
			return (1);
		}
	}
	return (0);
}

int	ft_fork(pid_t *pid, int prev_fd, int *fd)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork error");
		if (prev_fd != -1)
			close(prev_fd);
		if (fd[0] != -1)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return (1);
	}
	return (0);
}

int	edit_pipe_fd(t_command *cmd, int prev_fd, int *fd, t_data *data)
{
	if (handle_input_redirs(cmd, prev_fd, data) != 0)
		return (1);
	if (handle_output_redirs(cmd, fd, data) != 0)
		return (1);
	if (fd[0] != -1)
		close(fd[0]);
	return (0);
}

int	handle_input_redirs(t_command *cmd, int prev_fd, t_data *data)
{
	if ((cmd->heredoc_head && cmd->heredoc_head->filename) || cmd->infile)
	{
		if (open_input_redir(cmd, data) != 0)
			return (1);
	}
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			return (1);
		}
		close(cmd->fd_in);
	}
	else if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 prev_fd");
			return (1);
		}
		close(prev_fd);
	}
	return (0);
}

int	handle_output_redirs(t_command	*cmd, int *fd, t_data *data)
{
	if (cmd->outfile)
	{
		if (open_output_redir(cmd, data) != 0)
			return (1);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			close(cmd->fd_out);
			return (1);
		}
		close(cmd->fd_out);
	}
	else if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe write end");
			return ((close(fd[1])), 1);
		}
		close(fd[1]);
	}
	return (0);
}

/*
** ft_pipe : the function check if ther is a cmd and a next cmd. If the next
	is a PIPE, it create a pipe else it return an error.
** ft_fork : this function create a copy of the parent process : child
	process.
**edit_pipe_fd : 0 = stdin, 1 = stdout, -1 = this fd is invalid, this funtion
	is used inside the child process after fork() and it redirects input(stdin)
	if there is an input file if there is a prev pipe, it reads from the pipe.
	It also redirects output, if there is an input file it writes to that and
	if the command is followed by a pipe, it writes to the pipe.
	At the end it close all unused fd to avoid leaks. he fisrt part of the
	function is for the stdin, the stdout and for close all fd. 
*/
