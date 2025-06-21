/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:48:45 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/21 18:55:26 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

//typedef enum e_type
//{
//	CMD,
//	PIPE,
//	REDIR_IN,
//	REDIR_OUT,
//	APPEND,
//	HEREDOC
//}	t_type;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	char			*value;
	int				infile;
	int				outfile;
	t_token_type	type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;
	//t_type			type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
//key : the name of the variable
//value : valu of the variable
//ptr to the next variable

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
int		is_redir(t_cmd *cmd);
int		is_pipe(t_cmd *cmd);

// path utils
char	*find_path_variable(char **envp);
char	*try_paths(char **paths, char *cmd_name);
char	*get_path(char *cmd_name, char **envp);
void	free_split(char **tab);

//heredoc
void	child_heredoc(t_cmd *cmd, int *pipe_fd);
void	parent_heredoc(t_cmd *cmd, int *pipe_fd, int pid);
void	handle_heredoc_sigint(int sig);
void	handle_heredoc(t_cmd *cmd);
int		check_heredoc(t_cmd *cmd_list);

//signals
void	handle_sigint(int sig);
void	setup_parent_signals(void);
void	setup_child_signals(void);

//builtins

#endif