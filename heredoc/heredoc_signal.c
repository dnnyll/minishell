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
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (fill_heredoc(heredoc, cmd, data) == -1)
			exit(1);
		close(heredoc->fd);
		free_data_list(&data);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return (-1);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (-1);
	}
	return (0);
}
