/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_temp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:27:24 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:27:25 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(int pid, int index)
{
	char		*filename;
	char		*pid_str;
	char		*index_str;
	const char	*base;
	size_t		total_len;

	base = "/tmp/.heredoc_";
	pid_str = ft_itoa(pid);
	index_str = ft_itoa(index);
	if (!pid_str || !index_str)
		return (free(pid_str), free(index_str), NULL);
	total_len = ft_strlen(base) + ft_strlen(pid_str) + 1 + ft_strlen(index_str);
	filename = malloc(total_len + 1);
	if (!filename)
		return (free(pid_str), free(index_str), NULL);
	ft_strlcpy(filename, base, total_len + 1);
	ft_strlcat(filename, pid_str, total_len + 1);
	ft_strlcat(filename, "_", total_len + 1);
	ft_strlcat(filename, index_str, total_len + 1);
	free(pid_str);
	free(index_str);
	return (filename);
}

int	open_heredoc_filename(t_heredoc *heredoc)
{
	heredoc->filename = create_heredoc_filename(heredoc->pid, heredoc->index);
	if (!heredoc->filename)
		return (-1);
	heredoc->fd = open(heredoc->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc->fd == -1)
	{
		free(heredoc->filename);
		heredoc->filename = NULL;
		perror("open heredoc temp file");
		return (-1);
	}
	return (0);
}

int	write_line_to_heredoc(int fd, char *line)
{
	size_t	len;

	len = strlen(line);
	if (write(fd, line, len) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (0);
}

int	process_single_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	int	result;

	if (!heredoc->delimiter)
		return (0);
	if (open_heredoc_filename(heredoc) == -1)
		return (-1);
	result = manage_heredoc(cmd, data, heredoc);
	if (result == -1 || result == 1)
	{
		close(heredoc->fd);
		unlink_filename(data);
		return (-1);
	}
	close(heredoc->fd);
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = strdup(heredoc->filename);
	return (0);
}

int	process_heredocs(t_data *data)
{
	t_command	*cmd;
	t_heredoc	*heredoc;
	int			heredoc_index;

	cmd = data->command_head;
	heredoc_index = 0;
	while (cmd)
	{
		heredoc = cmd->heredoc_head;
		while (heredoc && cmd->heredoc_count > 0)
		{
			heredoc->index = heredoc_index++;
			if (process_single_heredoc(cmd, data, heredoc) == -1)
			{
				close(heredoc->fd);
				unlink_filename(data);
				return (-1);
			}
			heredoc = heredoc->next;
		}
		cmd->heredoc_count--;
		cmd = cmd->next;
	}
	return (0);
}
