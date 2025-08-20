/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:49:24 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/20 15:26:46 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int apply_redirs(t_command *cmd, int prev_fd, int *fd, t_data *data)
{
    // input first (stdin)
    if (handle_input_redirs(cmd, prev_fd, data) != 0)
        return (1);

    // then output (stdout)
    if (handle_output_redirs(cmd, fd, data) != 0)
        return (1);

    // close unused pipe read end
    if (fd[0] != -1)
        close(fd[0]);

    return (0);
}

// int	setup_redirection(t_command *command, t_data *data)
// {
// 	if (command->infile || command->heredoc_head->filename)
// 	{
// 		if (open_input_redir(command, data) != 0)
// 			return (1);
// 	}
// 	if (command->outfile)
// 	{
// 		if (open_output_redir(command, data) != 0)
// 			return (1);
// 	}
// 	return (0);
// }



// Handle input redirections (<)
int open_input_redir(t_command *cmd, t_data *data)
{
	t_redir *current;
	int fd;

	current = cmd->redir_in;
	while (current)
	{
		fd = open(current->filename, O_RDONLY);
		if (fd == -1)
		{
			data->last_exit_code_status = 1;
			write(2, "minishell: ", 11);
			write(2, current->filename, ft_strlen(current->filename));
			write(2, ": ", 2);
			perror(NULL);
			return (1);
		}
		if (cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		cmd->fd_in = fd;
		current = current->next;
	}
	return (0);
}

// Handle heredoc input redirections (<<)
int open_input_heredoc(t_command *cmd, t_data *data)
{
	t_heredoc *current;
	int fd;

	current = cmd->heredoc_head;
	while (current)
	{
		if (current->filename)
		{
			fd = open(current->filename, O_RDONLY);
			if (fd == -1)
			{
				data->last_exit_code_status = 1;
				write(2, "minishell: ", 11);
				write(2, current->filename, ft_strlen(current->filename));
				write(2, ": ", 2);
				perror(NULL);
				return (1);
			}
			if (cmd->fd_in != STDIN_FILENO)
				close(cmd->fd_in);
			cmd->fd_in = fd;
		}
		current = current->next;
	}
	return (0);
}

// Handle output redirections (> and >>)
int open_output_redir(t_command *cmd, t_data *data)
{
	t_redir *current;
	int fd;
	int flags;

	current = cmd->redir_out;
	while (current)
	{
		if (current->append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(current->filename, flags, 0644);
		if (fd == -1)
		{
			data->last_exit_code_status = 1;
			write(2, "minishell: ", 11);
			write(2, current->filename, ft_strlen(current->filename));
			write(2, ": ", 2);
			perror(NULL);
			return (1);
		}
		if (cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		cmd->fd_out = fd;
		current = current->next;
	}
	return (0);
}
void close_redirections(t_command *cmd)
{
	// Close heredoc FDs
	if (cmd->heredoc_head && cmd->heredoc_head->fd != -1)
	{
		close(cmd->heredoc_head->fd);
		cmd->heredoc_head->fd = -1;
	}

	// Close input redirection FD
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != -1)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}

	// Close output redirection FD
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out != -1)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

int setup_redirection(t_command *cmd, t_data *data)
{
	// Handle input redirections from files
	if (cmd->redir_in)
	{
		if (open_input_redir(cmd, data) != 0)
			return (1);
	}

	// Handle heredoc input redirections
	if (cmd->heredoc_head)
	{
		if (open_input_heredoc(cmd, data) != 0)
			return (1);
	}

	// Handle output redirections
	if (cmd->redir_out)
	{
		if (open_output_redir(cmd, data) != 0)
			return (1);
	}

	return (0);
}

// int	open_input_redir(t_command *command, t_data *data)
// {
// 	int		fd;
// 	char	*filename;

// 	fd = -1;
// 	filename = NULL;
// 	if (command->infile)
// 		filename = command->infile;
// 	else if (command->heredoc_head && command->heredoc_head->filename)
// 		filename = command->heredoc_head->filename;
// 	else
// 		return (0);
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		data->last_exit_code_status = 1;
// 		write(2, "minishell: ", 11);
// 		write(2, filename, ft_strlen(filename));
// 		write(2, ": ", 2);
// 		perror(NULL);
// 		return (1);
// 	}
// 	if (command->fd_in != STDIN_FILENO)
// 		close(command->fd_in);
// 	command->fd_in = fd;
// 	return (0);
// }

// int	open_output_redir(t_command *command, t_data *data)
// {
// 	int	fd;
// 	int	flags;

// 	if (!command->outfile)
// 		return (0);
// 	if (command->append)
// 		flags = O_WRONLY | O_CREAT | O_APPEND;
// 	else
// 		flags = O_WRONLY | O_CREAT | O_TRUNC;
// 	fd = open(command->outfile, flags, 0644);
// 	if (fd == -1)
// 	{
// 		print_error("minishell: ", command->outfile, ": ");
// 		perror(NULL);
// 		data->last_exit_code_status = 1;
// 		return (1);
// 	}
// 	if (command->fd_out != STDOUT_FILENO)
// 		close (command->fd_out);
// 	command->fd_out = fd;
// 	return (0);
// }

// void	close_redirections(t_command *command)
// {
// 	if (command->heredoc_head && command->heredoc_head->fd != -1)
// 	{
// 		close(command->heredoc_head->fd);
// 		command->heredoc_head->fd = -1;
// 	}
// 	if (command->fd_in != STDIN_FILENO && command->fd_in != -1)
// 	{
// 		close(command->fd_in);
// 		command->fd_in = -1;
// 	}
// 	if (command->fd_out != STDOUT_FILENO && command->fd_out != -1)
// 	{
// 		close(command->fd_out);
// 		command->fd_out = -1;
// 	}
// }
