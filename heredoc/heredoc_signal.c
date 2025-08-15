#include "minishell.h"

void	unlink_filename(t_data *data)
{
	t_heredoc	*current;
	t_heredoc	*next;
	int			i;

	if (!data || !data->command_head || !data->command_head->heredoc_head)
		return ;
	current = data->command_head->heredoc_head;
	i = data->command_head->heredoc_count;
	while (i > 0 && current)
	{
		next = current->next;
		if (current->filename)
			unlink(current->filename);
		current = next;
		i--;
	}
}

int	manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc)
{
	pid_t pid = fork();

	int	status;

	status = 0;
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (fill_heredoc(heredoc, cmd, data) == -1)
		{
			printf("======================== im here_05\n\n");
			exit(1);			//exit with error
		}
		close(heredoc->fd);
		free_data_list(&data);	// <========== frees if exit is correct
		exit(0);				//exit normal
	}
	else
	{
		printf("======================== im here_06\n\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (-1); // heredoc failed
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (-1);
	}
	return (0);
}

// void	handle_heredoc_sigint(int sig)
// {
// t_data *data;
// 	(void)sig;
// 	write(1, "\n", 1);
// data = ft_recup_data();
// free(data);
// 	exit(42);
// }


