#include "minishell.h"

int	manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, handle_heredoc_sigint);
		if (fill_heredoc(heredoc, cmd, data) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			g_signal_status = 130;
			return (130); // heredoc canceled
		}
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (1); // heredoc failed
	}
	return (0);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}