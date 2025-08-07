
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
			return (1);
		}
		close(cmd->fd_out);
	}
	else if (fd[1] != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe write end");
			return (1);
		}
		close(fd[1]);
	}
	return (0);
}

// DANIEFE2 __VERSION__int	edit_pipe_fd(t_command *cmd, int prev_fd, int *fd)
// {
// 	if ((cmd->heredoc_head && cmd->heredoc_head->filename) || cmd->infile)
// 	{
// 		if (open_input_redir(cmd) != 0)
// 			return (1);
// 	}
// 	if (cmd->outfile)
// 	{
// 		if (open_output_redir(cmd) != 0)
// 			return (1);
// 	}
// 	if (cmd->fd_in != STDIN_FILENO)
// 	{
// 		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 input");
// 			return (1);
// 		}
// 		close(cmd->fd_in);
// 	}
// 	else if (prev_fd != -1)
// 	{
// 		if (dup2(prev_fd, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 prev_fd");
// 			return (1);
// 		}
// 		close(prev_fd);
// 	}
// 	if (cmd->fd_out != STDOUT_FILENO)
// 	{
// 		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 output");
// 			return (1);
// 		}
// 		close(cmd->fd_out);
// 	}
// 	else if (fd[1] != -1)
// 	{
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 pipe write end");
// 			return (1);
// 		}
// 		close(fd[1]);
// 	}
// 	if (fd[0] != -1)
// 		close(fd[0]);

// 	return (0);
// }

//DEBUG VERSION:
// int edit_pipe_fd(t_command *cmd, int prev_fd, int *fd)
// {
// 	// Open input redirection if needed (heredoc or infile)
// 	if ((cmd->heredoc_head && cmd->heredoc_head->filename) || cmd->infile)
// 	{
// 		printf("Opening input redirection...\n");
// 		if (open_input_redir(cmd) != 0)
// 		{
// 			printf("Failed to open input redirection.\n");
// 			return (1);
// 		}
// 		printf("Input redirection opened successfully.\n");
// 	}

// 	// Open output redirection if needed (append or truncate)
// 	if (cmd->outfile)
// 	{
// 		printf("Opening output redirection...\n");
// 		if (open_output_redir(cmd) != 0)
// 		{
// 			printf("Failed to open output redirection.\n");
// 			return (1);
// 		}
// 		printf("Output redirection opened successfully.\n");
// 	}

// 	// Setup input
// 	if (cmd->fd_in != STDIN_FILENO)
// 	{
// 		printf("Duplicating cmd->fd_in (%d) to STDIN (%d)\n", cmd->fd_in, STDIN_FILENO);
// 		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
// 			return (perror("dup2 input"), 1);
// 		close(cmd->fd_in);
// 		printf("Closed cmd->fd_in\n");
// 	}
// 	else if (prev_fd != -1)
// 	{
// 		printf("Duplicating prev_fd (%d) to STDIN (%d)\n", prev_fd, STDIN_FILENO);
// 		if (dup2(prev_fd, STDIN_FILENO) == -1)
// 			return (perror("dup2 prev_fd"), 1);
// 		close(prev_fd);
// 		printf("Closed prev_fd\n");
// 	}

// 	// Setup output
// 	if (cmd->fd_out != STDOUT_FILENO)
// 	{
// 		printf("Duplicating cmd->fd_out (%d) to STDOUT (%d)\n", cmd->fd_out, STDOUT_FILENO);
// 		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
// 			return (perror("dup2 output"), 1);
// 		close(cmd->fd_out);
// 		printf("Closed cmd->fd_out\n");
// 	}
// 	else if (fd[1] != -1)
// 	{
// 		printf("Duplicating pipe write end (%d) to STDOUT (%d)\n", fd[1], STDOUT_FILENO);
// 		if (dup2(fd[1], STDOUT_FILENO) == -1)
// 			return (perror("dup2 pipe write end"), 1);
// 		close(fd[1]);
// 		printf("Closed pipe write end fd[1]\n");
// 	}

// 	// Close unused pipe read end
// 	if (fd[0] != -1)
// 	{
// 		close(fd[0]);
// 		printf("Closed unused pipe read end fd[0] (%d)\n", fd[0]);
// 	}

// 	printf("Finished setting up pipe and redirection fds.\n");
// 	return (0);
// }

//MROSSET VERSION
// void	edit_pipe_fd(t_command *cmd, int prev_fd, int *fd)
// {
// 	if (cmd->fd_in != STDIN_FILENO)
// 	{
// 		dup2(cmd->fd_in, STDIN_FILENO);
// 		close(cmd->fd_in);
// 	}
// 	else if (prev_fd != -1)
// 	{
// 		dup2(prev_fd, STDIN_FILENO);
// 		close(prev_fd);
// 	}
// 	if (cmd->fd_out != STDOUT_FILENO)
// 	{
// 		dup2(cmd->fd_out, STDOUT_FILENO);
// 		close(cmd->fd_out);
// 	}
// 	else if (fd[1] != -1)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 	}
// 	if (fd[0] != -1)
// 		close(fd[0]);
// }

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