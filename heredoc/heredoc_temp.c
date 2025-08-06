/* **************************************************************************** */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                           DEAD INSIDE                                        */
/*                                                                              */
/*                                                                              */
/*                                       MROSSET & DANIEFE2                     */
/*                                                                              */
/*                                                                              */
/* **************************************************************************** */

#include "minishell.h"

char	*create_heredoc_filename(int pid, int index)
{
	char	*filename;
	char	*pid_str;
	char	*index_str;
	const char *base;
	size_t	total_len;

	base = "/tmp/.heredoc_";
	pid_str = ft_itoa(pid);
	index_str = ft_itoa(index);
	if (!pid_str || !index_str)
		return (free(pid_str), free(index_str), NULL);
	total_len = ft_strlen(base) + ft_strlen(pid_str) + 1 + ft_strlen(index_str);
	filename = malloc(total_len + 1); // +1 for null terminator
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
	/*
	Open the temporary file for writing using open():
	O_CREAT: Create the file if it doesn’t exist yet.
	O_WRONLY: Open it for writing only — since we’ll write heredoc input into it.
	O_TRUNC: If the file exists, truncate it (empty it) before writing new content.
	0644: This sets file permissions — meaning:
		Owner can read/write (6 = 4 + 2)
		Group can read only (4)
		Others can read only (4)
	*/
	if (heredoc->fd == -1)
	{
		free(heredoc->filename);
		heredoc->filename = NULL;
		perror("open heredoc temp file");
		return (-1);
	}
	printf("heredoc fd=%d filename=%s\n", heredoc->fd, heredoc->filename);
	return (0);
}
/*
Step 4: Read lines from user until delimiter

You need to:
    Prompt the user with readline("> ")
    Keep reading lines
    If the line matches the delimiter, stop
    Otherwise, write the line into the open heredoc file (followed by a newline)
*/

int	write_line_to_heredoc(int fd, char *line)
{
	size_t	len;

	len = strlen(line);
	if (write(fd, line, len) == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	printf("Wrote line to heredoc\n");
	return (0);
}

void	heredoc_cleanup(t_heredoc *heredoc)
{
	printf("heredoc_cleanup\n");
	if (!heredoc)
		return ;
	if (heredoc->filename)
	{
		free(heredoc->filename);
		heredoc->filename = NULL;
	}
	free(heredoc);
}

int	process_single_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	int	result;

	printf("Processing heredoc: %s\n", heredoc->delimiter);
	if (!heredoc->delimiter)
		return (0);
	if (open_heredoc_filename(heredoc) == -1)
		return (-1);
	result = manage_heredoc(cmd, data, heredoc);
	if (result == -1 || result == 1)
		return (-1);
	close(heredoc->fd);
	if (cmd->infile)
	{
		printf("Freeing old infile: %s\n", cmd->infile);
		free(cmd->infile);
	}
	cmd->infile = strdup(heredoc->filename);
	return (0);
}

int	process_heredocs(t_data *data)
{
	t_command	*cmd = data->command_head;
	t_heredoc	*heredoc;
	int			heredoc_index;

	heredoc_index = 0; // used only for assigning to heredoc->index
	while (cmd)
	{
		heredoc = cmd->heredoc_head;
		while (heredoc && cmd->heredoc_count > 0)
		{
			heredoc->index = heredoc_index++;  // use struct's index field
			if (process_single_heredoc(cmd, data, heredoc) == -1)
			{
				heredoc_cleanup(heredoc);
				return (-1);
			}
			heredoc = heredoc->next;
		}
		cmd->heredoc_count--;
		cmd = cmd->next;
	}
	return (0);
}
