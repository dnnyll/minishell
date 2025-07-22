/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:26:50 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/09 10:00:30 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_command *cmd, int *fd)
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

void	edit_pipe_fd(t_command *cmd, int prev_fd, int *fd)
{
	//gestion de l'entree
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	//getion de la sortie
	if (cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	else if (fd[1] != -1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	//ferme les 2 fd du pipe
	if (fd[0] != -1)
		close(fd[0]);
	//if (fd[1] != -1)
		//close(fd[1]);
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