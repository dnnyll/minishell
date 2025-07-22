/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:23:58 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/22 17:15:26 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	child_heredoc(t_command *cmd, int *pipe_fd)
// {
// 	char	*line;

// 	signal(SIGINT, handle_heredoc_sigint);
// 	close(pipe_fd[0]);
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line
// 			|| ft_strncmp(line, cmd->value, ft_strlen(cmd->value) + 1) == 0)
// 			break ;
// 		write (pipe_fd[1], line, ft_strlen(line));
// 		write (pipe_fd[1], "\n", 1);
// 		free(line);
// 	}
// 	free(line);
// 	close(pipe_fd[1]);
// 	exit(0);
// }

char	*expand_line(char *line, t_command *cmd, t_data *data)
{
	printf("%p\n\n", (void *)data->env_head);
	if (cmd->heredoc_quoted == false && data->env_head)
		return (expand_variables(line, data));
	else
		return (ft_strdup(line));
}

void	child_heredoc(t_command *cmd, int *pipe_fd, t_data *data)
{
	(void)data;
	printf("DEBUG: child_heredoc started for delim = %s\n", cmd->heredoc_delim);
	char	*line;
	// char	*expanded;

	signal(SIGINT, handle_heredoc_sigint);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->heredoc_delim, ft_strlen(cmd->heredoc_delim) + 1) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		// expanded = expand_line(line, cmd, data);	// <-- HERE is where data->env is checked inside expand_line
		// write(pipe_fd[1], expanded, ft_strlen(expanded));
		write(pipe_fd[1], "\n", 1);
		// free(expanded);
		free(line);
	}
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

void	handle_heredoc(t_command *cmd, t_data *data)
{
	int	pid;
	int	pipe_fd[2];

	printf("DEBUG: handle_heredoc called for delim = %s\n", cmd->heredoc_delim);
	if (pipe(pipe_fd) == -1)
		return (perror("heredoc pipe : failed"));
	pid = fork();
	if (pid == -1)
		return (perror("heredoc fork : failed"));
	if (pid == 0)
		child_heredoc(cmd, pipe_fd, data);
	else
		parent_heredoc(cmd, pipe_fd, pid);
}

// int	check_heredoc(t_command *cmd_list)
// {
// 	while (cmd_list)
// 	{
// 		if (cmd_list->heredoc_delim)
// 		{
// 			handle_heredoc(cmd_list);
// 			if (cmd_list->fd_in == -1)
// 				return (1);
// 		}
// 		cmd_list = cmd_list->next;
// 	}
// 	return (0);
// }

int check_heredoc(t_command *cmd_list, t_data *data)
{
	while (cmd_list)
	{
		if (cmd_list->heredoc_delim)
		{
			handle_heredoc(cmd_list, data);
			if (cmd_list->fd_in == -1)
				return 1;
		}
		cmd_list = cmd_list->next;
	}
	return 0;
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

/**********************************************
 *                HEREDOC TESTS                *
 *                                            *
 * Test 1:                                    *
 * $ ./minishell                             *
 * minishell> cat << EOF                     *
 * token                                     *
 * $HOME                                     *
 * $USER                                     *
 * EOF                                       *
 * Expected: Variables $HOME and $USER are   *
 * expanded inside heredoc output.            *
 *                                            *
 * Test 2: Quoted delimiter                    *
 * $ ./minishell                             *
 * minishell> cat << "EOF"                   *
 * token                                     *
 * $HOME                                     *
 * $USER                                     *
 * EOF                                       *
 * Expected: No variable expansion; output    *
 * literal $HOME and $USER.                   *
 *                                            *
 * Test 3: No heredoc                         *
 * $ ./minishell                             *
 * minishell> echo $USER                     *
 * Expected: $USER expands normally outside   *
 * heredoc.                                   *
 **********************************************/