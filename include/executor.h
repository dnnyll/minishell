/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:48:45 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/01 15:41:58 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_cmd
{
	char			**args; // tab for cmds
	char			*path; // path to executor
	char			*value;
	int				infile;
	int				outfile;
	t_type			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef enum e_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_type;

//pipe utils
int		ft_pipe(t_cmd *cmd, int *fd);
int		ft_fork(pid_t *pid, int prev_pipe_read, int *fd);
void	edit_pipe_fd(int infile, int outfile, int prev_pipe_read, int *fd);
//execution
void	child_process(t_cmd *cmd, int prev_pipe_read, int *fd, char **env_vars);
int		parent_process(int prev_pipe_read, int *fd);
void	execute_pipeline(t_cmd *cdm_list, char **env_vars);
//commands utils
int		is_command(t_cmd *cmd);
int		is_redirection(t_cmd *cmd);
int		is_pipe(t_cmd *cmd);

#endif