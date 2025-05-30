/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:26:50 by mrosset           #+#    #+#             */
/*   Updated: 2025/05/30 12:45:04 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_cmd *cmd, int *fd)
{
	fd[0] = -1;
	fd[1] = -1;

	if (cmd && cmd->next && cmd->next->type == PIPE)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe error\n");
			return (1);
		}
	}
	return (0);
}

int	ft_fork(pid_t *pid, int prev_pipe_read, int *fd)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork error\n");
		if (prev_pipe_read != -1)
			close(prev_pipe_read);
		if (fd[0] != -1)
		{
			close(fd[0]);
			close(fd[1]);
		}
		return (1);
	}
	return (0);
}

/*
** ft_pipe : the function check if ther is a cmd and a next cmd. If the next
	is a PIPE, it create a pipe else it return an error.
** ft_fork : this function create a copy of the parent process : child
	process. 
*/