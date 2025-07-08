/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:23:58 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/15 14:38:04 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_heredoc(t_command *cmd, int *pipe_fd)
{
	char	*line;

	signal(SIGINT, handle_heredoc_sigint);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line
			|| ft_strncmp(line, cmd->value, ft_strlen(cmd->value) + 1) == 0)
			break ;
		write (pipe_fd[1], line, ft_strlen(line));
		write (pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	exit(0);
}

void	parent_heredoc(t_command *cmd, int *pipe_fd, int pid)
{
	int	status;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		cmd->fd_in = -1;
	else
		cmd->fd_in = pipe_fd[0];
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	handle_heredoc(t_command *cmd)
{
	int	pid;
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("heredoc pipe : failed"));
	pid = fork();
	if (pid == -1)
		return (perror("heredoc fork : failed"));
	if (pid == 0)
		child_heredoc(cmd, pipe_fd);
	else
		parent_heredoc(cmd, pipe_fd, pid);
}

int	check_heredoc(t_command *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->type == HEREDOC)
		{
			handle_heredoc(cmd_list);
			if (cmd_list->fd_in == -1)
				return (1);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}

/*
**child_heredoc : read user input line by line until delimiter is reached. Each
	line is written to the write-end of the pipe. Once done, close the pipe and
	exit.
**parent_heredoc : close the write-end of the pipe, wait for the child process
	to finish. If the chils was interrupted by a signal, set fd_in to -1.
	Otherwise, set fd_in to the read-end of the pipe.
**handle_heredoc : create the heredoc, use a pipe to write the process child
	to read it from the parent process. Create a child process (fork) to read
	the heredoc input and the parent recover what the child wrote in the pipe.
	pipe_fd[0] = reading / pipe_fd[1] = writing.
**handle_heredoc_signit : special signal handler for heredoc, 130 is the
	standard code for Ctrl+C in heredoc.
**check_heredoc : go through each command int the list. If a heredoc is found,
	call handle_heredoc. If any heredoc was interrupted (fd_in == -1),
	return 1 to indicate an error.
*/