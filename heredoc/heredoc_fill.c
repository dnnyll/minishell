/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:26:50 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:26:53 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_expanded_line(char *line, t_data *data, int *should_free)
{
	*should_free = 0;
	if (!line)
		return (NULL);
	*should_free = 1;
	return (expand_variables(line, data));
}

static int	write_and_free_line(char *line, int should_free, int fd)
{
	if (write_line_to_heredoc(fd, line) == -1)
	{
		free(line);
		return (-1);
	}
	if (should_free)
		free(line);
	return (0);
}

static int	heredoc_expansion(t_data *data, char *line,
	char **expanded, int *should_free)
{
	if (data->command_head->heredoc_head->quoted)
	{
		*expanded = line;
		*should_free = 0;
	}
	else
	{
		*expanded = get_expanded_line(line, data, should_free);
		free(line);
		if (!*expanded)
			return (-1);
	}
	return (0);
}

int	fill_heredoc(t_heredoc *heredoc, t_command *cmd, t_data *data)
{
	char	*line;
	char	*expanded;
	int		should_free;

	if (!heredoc || !cmd || !heredoc->delimiter)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_warning(heredoc->delimiter);
			return (free_data_list(&data), -1);
		}
		if (is_delimiter_match(line, heredoc->delimiter))
			return (free(line), 0);
		if (heredoc_expansion(data, line, &expanded, &should_free) == -1)
			return (-1);
		if (write_and_free_line(expanded, should_free, heredoc->fd) == -1)
			return (-1);
	}
	return (0);
}
