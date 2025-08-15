#include "minishell.h"

int	is_delimiter_match(char *line, char *delim)
{
	return (ft_strncmp(line, delim, ft_strlen(delim)) == 0
		&& line[ft_strlen(delim)] == '\0');
}

void	print_heredoc_warning(char *delim)
{
	write(2, "minishell: warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 32);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}
