/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:26:50 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/05 12:48:56 by mrosset          ###   ########.fr       */
/*   Updated: 2025/06/05 11:56:45 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_cmd *cmd, int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
	if (cmd && cmd->next && cmd->next->type == PIPE)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe error");
			return (1);
		}
	}
	return (0);
}

int	ft_fork(pid_t *pid, int prev_pipe_read, int *fd)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork error");
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		if (fd[0] != -1)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return (1);
	}
	return (0);
}

void	edit_pipe_fd(int infile, int outfile, int prev_pipe_read, int *fd)
{
	if (infile != 0)
	{
		dup2(infile, 0);
		close(infile);
	}
	else if (prev_pipe_read != -1)
	{
		dup2(prev_pipe_read, 0);
		close(prev_pipe_read);
	}
	if (outfile != 1)
	{
		dup2(outfile, 1);
		close(outfile);
	}
	else if (fd[1] != -1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (fd[0] != -1)
		close(fd[0]);
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
	At the end it close all unused fd to avoid leaks.
*/