#include "minishell.h"

int	manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	printf("fill_heredoc: heredoc ptr = %p\n", (void *)heredoc);
	printf("fill_heredoc: cmd->heredoc_head ptr = %p\n", (void *)cmd->heredoc_head);
	pid_t pid = fork();	// creates the child process
	int	status;

	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		// child process
		printf("CASE_0 (child process)\n");
		// Set signal handler for heredoc input (handle Ctrl+C differently here)
		signal(SIGINT, handle_heredoc_sigint);
		if (fill_heredoc(heredoc, cmd, data) == -1)
		{
			printf("exit with error from fill_heredoc");
			// free_data_list(&data);
			exit(1); //exit with error
		}
		free_data_list(&data);
		exit(0);	//exit normal
	}
	else
	{
		// free_data_list(&data);

		//parent process
		waitpid(pid, &status, 0);
		printf("CASE_1\n");
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			printf("CASE_2 (child exited with error, we are at parent)\n");
			free_data_list(&data);
			return (-1); // heredoc failed
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			printf("CASE_3 (child was killed by SIGINT)\n");
			free_data_list(&data);
			return (-1);
		}
		// else
		// {
		// 	printf("CASE_2 (child exited with error, we are at parent)\n");
		// 	free_data_list(&data);
		// 	return (-1); // heredoc failed
		// }
	}
	// free_data_list(&data);
	return (0);
}

void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}
