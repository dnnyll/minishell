#include "minishell.h"

static int	is_delimiter_match(char *line, char *delim)
{
	return (ft_strncmp(line, delim, ft_strlen(delim)) == 0
		&& line[ft_strlen(delim)] == '\0');
}

static void	print_heredoc_warning(char *delim)
{
	write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 66);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}

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
		return (free(line), -1);
	if (should_free)
		free(line);
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
			return (print_heredoc_warning(heredoc->delimiter), 0);
		if (is_delimiter_match(line, heredoc->delimiter))
			return (free(line), 0);
		if (heredoc->quoted)
			expanded = line, should_free = 0;
		else
		{
			expanded = get_expanded_line(line, data, &should_free);
			free(line);
			if (!expanded)
				return (-1);
		}
		if (write_and_free_line(expanded, should_free, heredoc->fd) == -1)
			return (-1);
	}
}
