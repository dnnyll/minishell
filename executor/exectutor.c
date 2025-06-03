/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:16:25 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/01 15:42:23 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmd *cmd, int prev_pipe_read, int *fd, char **env_vars)
{
	edit_pipe_fd(cmd->infile, cmd->outfile, prev_pipe_read, fd);
	if (execve(cmd->path, cmd->args, env_vars) == -1)
	{
		perror("execve failed");
		exit(1);
	}
}

int	parent_process(int prev_pipe_read, int *fd)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	if (fd[1] != -1)
		close(fd[1]);
	if (fd[0] != -1)
		return (fd[0]);
	return (-1);
}

void	execute_pipeline(t_cmd *cdm_list, char **env_vars)
{
	t_cmd	*cmd;
	int		fd[2];
	int		prev_pipe_read;
	pid_t	pid;

	cmd = cmd_list;
	prev_pipe_read = -1;
	while (cmd)
	{
		if (ft_pipe(cmd, fd))
			return ;
		if (ft_fork(&pid, prev_pipe_read, fd))
			return ;
		if (pid == 0)
			child_process(cmd, prev_pipe_read, fd, env_vars);
		prev_pipe_read = parent_process(prev_pipe_read, fd);
		cmd = cmd->next;
	}
	pid = 1;
	while (pid > 0)
		pid = wait(NULL);
}

/*
** child_process : prepare the redirection in/out and replace the actual
	process with the command to execute, else display an error.
** parent_process : is called just after fork() to close old unsused fd.
	And to prepare the next pipeline.
** execute_pipeline : execute all commands from t_cmd with or without pipe
	in  while loop.
*/