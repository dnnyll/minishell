/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:16:25 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/06 17:58:06 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_command **argv)
{
	if (!argv || !*argv || !(*argv)->argv || !(*argv)->argv[0])
		return (false);
	if (ft_strncmp((*argv)->argv[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "unset", 6) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "exit", 5) == 0)
		return (true);
	return (false);
}

void	child_process(t_command *cmd, int prev_pipe_read, int *fd, char **env_vars)
{
	char	*path;

	edit_pipe_fd(cmd->infile, cmd->outfile, prev_pipe_read, fd);
	setup_child_signals();
	path = get_path(cmd->argv[0], env_vars);
	if (!path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		exit(127);
	}
	cmd->path = path;
	if (execve(cmd->path, cmd->argv, env_vars) == -1)
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

void	execute_pipeline(t_command *cmd_list, char **env_vars)
{
	t_command	*cmd;
	int			fd[2];
	int			prev_pipe_read;
	pid_t		pid;

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
** is_buitlins : !argv->the cmd ptr is NULL, !*argv->the cmd pointed to is
	NULL, !(*argv)->agv -> the argv array(the cmds argv)doesn't exist, 
	!(*argv)->argv[0]-> there is no cmd(empt line). If any ot htese conditions
	is true, it's not a valid command, so we return false.
	This function is for check if the cmd is a buitlins or not, ft_strncmp
	compare each char of argv[0] and return true if it match.
** child_process : prepare the redirection in/out and replace the actual
	process with the command to execute, else display an error. Default
	behaviors are restored for SIGINY and SIGQUIT signals. And search
	the complete path of the cmd to execute. If the cmd is NULL (or not found),
	display an error message on the error output and quit with the standard
	code 127 (mean command not found). Stock the path in cmd to use it.
** parent_process : is called just after fork() to close old unsused fd.
	And to prepare the next pipeline.
** execute_pipeline : execute all commands from t_command with or without pipe
	in  while loop.
*/