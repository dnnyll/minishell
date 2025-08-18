/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:26:59 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/18 11:55:51 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (g_signal_status = 1, -1);
	}
	return (0);
}
