#include "minishell.h"

int	manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	pid_t pid = fork();
	int	status;

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
		// if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		// {
		// 	printf ("HERE IS THE SINGLA CTRL + C ??????????\n\n\n");
		// 	// g_signal_status = 130;
		// 	// unlink(heredoc->filename);
		// 	// heredoc_cleanup(heredoc);
		// 	printf("2\n");
		// 	// free_commands(data);
		// 	return (130); // heredoc canceled
		// }
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (-1); // heredoc failed
	}
	return (0);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// raise(SIGINT); // Re-raise the signal to kill the process
	// signal(SIGINT, SIG_DFL);
	// kill(getpid(), SIGINT);
	exit(1);
}