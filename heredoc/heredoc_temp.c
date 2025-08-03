#include "minishell.h"

char	*create_heredoc_filename(int id)
{
	char	*filename;
	char	*id_str;
	const	char *base;
	size_t	base_len;
	size_t	id_len;

	base = "/tmp/.heredoc_";
	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	base_len = ft_strlen(base);
	id_len = ft_strlen(id_str);
	filename = malloc(base_len + id_len + 1);
	if (!filename)
	{
		free(id_str);
		return NULL;
	}
	ft_strlcpy(filename, base, (base_len + id_len + 1));
	ft_strlcpy(filename + base_len, id_str, (base_len + id_len + 1));
	free(id_str);
	return (filename);
}

int	open_heredoc_filename(t_heredoc *heredoc)
{
	heredoc->filename = create_heredoc_filename(heredoc->pid);
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
	{
		printf("!heredoc\n");
		return;
	}
	if (heredoc->filename)
	{
		printf("Leaving heredoc file intact for now: %s\n", heredoc->filename);
		// unlink(heredoc->filename);
		free(heredoc->filename);
		
		heredoc->filename = NULL;
	}
	free(heredoc);
}

int	process_heredocs(t_data *data)
{
	t_command *cmd = data->command_head;
	int	id;
	int	result;

	id = 0;
	while (cmd)
	{
		if (cmd->heredoc_delim)
		{
			t_heredoc *heredoc = init_heredoc(id);
			if (!heredoc || open_heredoc_filename(heredoc) == -1)
			{
				heredoc_cleanup(heredoc);
				return (-1);
			}
			result = manage_heredoc(cmd, data, heredoc);
			printf("THIS IS THE RESULT= %d\n\n\n", result);
			// if (result == 130)
			// {
			// 	heredoc_cleanup(heredoc);
			// 	unlink(heredoc->filename);
			// 	return (130); // Stop execution
			// }
			if (result == -1 || result == 1)
			{
				heredoc_cleanup(heredoc);
				return (-1);
			}
			close(heredoc->fd);
			cmd->infile = strdup(heredoc->filename);
			heredoc_cleanup(heredoc);
			unlink(heredoc->filename);
			id++;
		}
		cmd = cmd->next;
	}
	return (0);
}


