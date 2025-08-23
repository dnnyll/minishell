/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:16:58 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/23 15:19:35 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_outfiles(char **outfiles)
{
	int	i;

	i = 0;
	if (!outfiles)
		return ;
	while (outfiles[i])
	{
		free(outfiles[i]);
		i++;
	}
	free(outfiles);
}

static int	open_outfile(const char *filename, int append)
{
	int	fd;

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

static int	handle_outfiles(char **outfiles, int *append_flags)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (outfiles[i])
	{
		if (fd >= 0)
			close(fd);
		fd = open_outfile(outfiles[i], append_flags[i]);
		i++;
	}
	return (fd);
}

static void	redirect_stdout(int fd)
{
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	setup_outfiles(t_command *cmd)
{
	cmd->fd_out = handle_outfiles(cmd->outfile, cmd->append_flags);
	redirect_stdout(cmd->fd_out);
}
