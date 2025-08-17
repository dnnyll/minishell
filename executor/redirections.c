/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:49:24 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/17 13:53:29 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_redirection(t_command *command, t_data *data)
{
	if (command->infile || command->heredoc_head->filename)
	{
		if (open_input_redir(command, data) != 0)
			return (1);
	}
	if (command->outfile)
	{
		if (open_output_redir(command, data) != 0)
			return (1);
	}
	return (0);
}

int	open_input_redir(t_command *command, t_data *data)
{
	int		fd;
	char	*filename;

	fd = -1;
	filename = NULL;
	if (command->infile)
		filename = command->infile;
	else if (command->heredoc_head && command->heredoc_head->filename)
		filename = command->heredoc_head->filename;
	else
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		data->last_exit_code_status = 1;
		write(2, "minishell: ", 11);
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
		perror(NULL);
		return (1);
	}
	if (command->fd_in != STDIN_FILENO)
		close(command->fd_in);
	command->fd_in = fd;
	return (0);
}

int	open_output_redir(t_command *command, t_data *data)
{
	int	fd;
	int	flags;

	if (!command->outfile)
		return (0);
	if (command->append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(command->outfile, flags, 0644);
	if (fd == -1)
	{
		print_error("minishell: ", command->outfile, ": ");
		perror(NULL);
		data->last_exit_code_status = 1;
		return (1);
	}
	if (command->fd_out != STDOUT_FILENO)
		close (command->fd_out);
	command->fd_out = fd;
	return (0);
}

void	close_redirections(t_command *command)
{
	if (command->heredoc_head && command->heredoc_head->fd != -1)
	{
		close(command->heredoc_head->fd);
		command->heredoc_head->fd = -1;
	}
	if (command->fd_in != STDIN_FILENO && command->fd_in != -1)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if (command->fd_out != STDOUT_FILENO && command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}
