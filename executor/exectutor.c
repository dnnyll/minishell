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

// void	child_process(t_command *cmd, int prev_fd, int *fd, char **env_vars)
// {
// 	char	*path;

// 	edit_pipe_fd(cmd, prev_fd, fd);
// 	setup_child_signals();
// 	path = get_path(cmd->argv[0], env_vars);
// 	if (fd)
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	if (!path)
// 	{
// 		write(2, "minishell: command not found: ", 30);
// 		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
// 		write(2, "\n", 1);
// 		exit(127);
// 	}
// 	cmd->path = path;
// 	if (execve(cmd->path, cmd->argv, env_vars) == -1)
// 	{
// 		perror("execve failed");
// 		exit(1);
// 	}
// }

void	child_process(t_command *cmd, int prev_fd, int *fd, char **env_vars)
{
	char	*path;

	edit_pipe_fd(cmd, prev_fd, fd);
	setup_child_signals();
	path = get_path(cmd->argv[0], env_vars);
	if (!path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, "\n", 1);
		exit(127);
	}
	execve(path, cmd->argv, env_vars);
	perror("execve failed");
	exit(1);
}

int	parent_process(int prev_fd, int *fd)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (fd[1] != -1)
		close(fd[1]);
	//if (fd[0] != -1)
	return (fd[0]);
	//return (-1);
}

void	execute_buitlins(t_command *cmd, t_data *data)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		echo_builtin(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		cd_builtin(cmd->argv, data->environment_var);
	else if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		pwd_builtin(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		export_builtin(cmd->argv, data);
	else if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		unset_builtin(cmd->argv, data);
	else if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		env_builtin(data);
	else if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		exit_builtin(cmd->argv, data);
}

void	execute_commands(t_command *cmd_list, t_data *data)
{
	if (!cmd_list)
		return ;
	if (check_heredoc(cmd_list))
		return ;
	if (!cmd_list->next && is_builtin(&cmd_list))
		execute_buitlins(cmd_list, data);
	else
		execute_pipeline(cmd_list, data->environment_var);
}

void	execute_pipeline(t_command *cmd_list, char **env_vars)
{
	t_command	*cmd;
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	int			status;

	cmd = cmd_list;
	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next)
		{
			if (ft_pipe(cmd, fd))
				return ;
		}
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		if (ft_fork(&pid, prev_fd, fd))
			return ;
		if (pid == 0)
			child_process(cmd, prev_fd, fd, env_vars);
		prev_fd = parent_process(prev_fd, fd);
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	// pid = wait(&status);
	// while (pid > 0)
	// 	pid = wait(&status);
	while (waitpid(-1, &status, 0) > 0)
		;
}
/*
** child_process : prepare the redirection in/out and replace the actual
	process with the command to execute, else display an error. Default
	behaviors are restored for SIGINY and SIGQUIT signals. And search
	the complete path of the cmd to execute. If the cmd is NULL (or not found),
	display an error message on the error output and quit with the standard
	code 127 (mean command not found). Stock the path in cmd to use it.
** parent_process : is called just after fork() to close old unsused fd.
	And to prepare the next pipeline.
** execute_buitlins : This function is for execute a builtin if this is one,
	check if cmd and cmd->argv[0] are valid and compare the name with strncmp, 
	then call the right buitlins with goods args
**execute_commands : Decides how to execute a list of commands. If it'a a single
	builtin, executed directly int the parent. Or a cmd pipeline with fork and
	pipes.
** execute_pipeline : execute all commands from t_command with or without pipe
	in  while loop.
*/