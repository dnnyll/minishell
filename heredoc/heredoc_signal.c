#include "minishell.h"

int	manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		printf("WE HAVE ENTERED PID == 0\n\n\n");
		signal(SIGINT, handle_heredoc_sigint);
		if (fill_heredoc(heredoc, cmd, data) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (-1);
	}
	return (0);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
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
