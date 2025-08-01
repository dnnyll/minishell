#include "minishell.h"
/*
+----------------------------------------------------------+
|                     HEREDOC FLOW OVERVIEW                |
+----------------------------------------------------------+
|                                                          |
| 1) Check each command if heredoc is needed                |
|    - Function: check_heredoc(command_list, data)              |
|    - Iterates through command_list                             |
|                                                          |
| 2) For each heredoc command:                               |
|    -> Create a temporary file for heredoc input           |
|       - Function: create_heredoc_tempfile()                |
|       - Returns open fd and filename                        |
|                                                          |
| 3) Fork a child process                                    |
|    - In child:                                             |
|      * Read user lines with readline("> ")                |
|      * Expand variables if not quoted                      |
|        - Function: expand_line(line, command, data)            |
|      * Write each line + newline into tempfile             |
|      * Close write fd, exit                                |
|      - Function: child_heredoc(command, fd, data)              |
|                                                          |
|    - In parent:                                            |
|      * Wait for child to finish                            |
|      * Close write fd                                      |
|      * Reopen tempfile for reading (O_RDONLY)              |
|      * Set command->fd_in = read fd for later input redirection|
|      - Function: parent_heredoc(command, fd, pid)               |
|                                                          |
| 4) During command execution:                               |
|    - Use command->fd_in as input (dup2 to STDIN)               |
|    - Continue with execve for command                      |
|                                                          |
| 5) Cleanup (optionally):                                   |
|    - Delete tempfile after command done                    |
|                                                          |
+----------------------------------------------------------+
|                        SUMMARY                            |
|                                                          |
| [check_heredoc]      -> scans commands for heredoc       |
| [create_heredoc_tempfile] -> safely creates temp file     |
| [child_heredoc]      -> reads user input, writes to file  |
| [parent_heredoc]     -> waits, reopens file for reading   |
| [expand_line]        -> expands variables in heredoc line |
| command->fd_in           -> input fd for command execution    |
+----------------------------------------------------------+
*/

/*
What have we done so far:

    We discussed creating a struct to hold heredoc info (filename, delimiter, quoted or not, fd).

    You want to generate the heredoc filename dynamically.

    You want to write heredoc lines into this temporary file.

    We decided to fork a child process to read lines with readline, do expansions if necessary, and write them to the temp file.

    The parent process waits for the child and then will use the temp file as input.

Next steps:

    Create the temporary file with a unique name. <++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    Fork the child process to read and write heredoc lines to that file.

    Close the write end and open the file for reading in the parent.

    Assign the file descriptor to the command’s fd_in to redirect input late
*/

/*+-----------------------------------------------+
|               Heredoc Filename Setup          |
+-----------------------------------------------+
|                                               |
|  [int_to_str(int n)]                           |
|       Converts integer to string               |
|                                               |
|  [get_pid_str()]                              |
|       - Calls getpid()                         |
|       - Returns pid as string (via int_to_str)|
|                                               |
|  [get_counter_str(int counter)]                |
|       - Converts counter to string             |
|                                               |
|  [generate_heredoc_filename(int counter)]     |
|       - Calls get_pid_str()                    |
|       - Calls get_counter_str(counter)         |
|       - Concatenates:                          |
|         "/tmp/.heredoc_" + pid_str + "_" +    |
|          counter_str                           |
|       - Frees pid_str & counter_str            |
|       - Returns full filename string           |
+-----------------------------------------------+
*/

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
int	fill_heredoc(t_heredoc *heredoc, t_command *command, t_data *data)
{
	char	*line;
	char	*expanded_line;
	int		should_free;

	if (!heredoc || !command || !command->heredoc_delim)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 66);
			write(2, command->heredoc_delim, ft_strlen(command->heredoc_delim));
			write(2, "`)\n", 3);
			break ;
		}
			if (ft_strncmp(line, command->heredoc_delim, ft_strlen(command->heredoc_delim)) == 0
			&& line[ft_strlen(command->heredoc_delim)] == '\0')
		{
			free(line);
			break;
		}
		if (command->heredoc_quoted == 0)
		{
			expanded_line = expand_variables(line, data);
			free(line);
			if (!expanded_line)
				return (-1);
			should_free = 1;
		}
		else
		{
			expanded_line = line;
			should_free = 0;
		}
		if (write_line_to_heredoc(heredoc->fd, expanded_line) == -1)
		{
			if (should_free)
				free(expanded_line);
			else
				free(line);
			return (-1);
		}
		if (should_free)
			free(expanded_line);
		else
			free(line);
	}
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


