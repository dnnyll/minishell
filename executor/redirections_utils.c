#include "minishell.h"

void free_outfiles(char **outfiles)
{
	int i;
	
	i = 0;
	if (!outfiles)
		return;

	while (outfiles[i])
	{
		free(outfiles[i]);
		i++;
	}
	free(outfiles);
}

static int open_outfile(const char *filename, int append)
{
	int fd;

	if (append)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd < 0)
	{
		perror(filename);
		exit(1);
	}
	return (fd);
}

static int handle_outfiles(char **outfiles, int *append_flags)
{
	int i = 0;
	int fd = -1;

	while (outfiles[i])
	{
		if (fd >= 0)
			close(fd);

		fd = open_outfile(outfiles[i], append_flags[i]);
		i++;
	}
	return (fd);
}

static void redirect_stdout(int fd)
{
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void setup_outfiles(t_command *cmd)
{
	cmd->fd_out = handle_outfiles(cmd->outfile, cmd->append_flags);
	redirect_stdout(cmd->fd_out);
}
