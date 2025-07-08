/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:48:45 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/25 15:06:48 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// typedef struct s_cmd
// {
// 	char			**args;
// 	char			*path;
// 	char			*value;
// 	int				infile;
// 	int				outfile;
// 	t_token_type	type;
// 	struct s_cmd	*next;
// 	struct s_cmd	*prev;
// }	t_command;
	//t_type			type;

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }	t_env;
//key : the name of the variable
//value : valu of the variable
//ptr to the next variable

//pipe utils
int		ft_pipe(t_command *cmd, int *fd);
int		ft_fork(pid_t *pid, int prev_pipe_read, int *fd);
void	edit_pipe_fd(int infile, int outfile, int prev_pipe_read, int *fd);

//execution
void	child_process(t_command *cmd, int prev_pipe_read, int *fd, char **env_vars);
int		parent_process(int prev_pipe_read, int *fd);
void	execute_pipeline(t_command *cdm_list, char **env_vars);

//commands utils
int		is_command(t_command *cmd);
int		is_redir(t_command *cmd);
int		is_pipe(t_command *cmd);

// path utils
char	*find_path_variable(char **envp);
char	*try_paths(char **paths, char *cmd_name);
char	*get_path(char *cmd_name, char **envp);
void	free_split(char **tab);

//heredoc
void	child_heredoc(t_command *cmd, int *pipe_fd);
void	parent_heredoc(t_command *cmd, int *pipe_fd, int pid);
void	handle_heredoc_sigint(int sig);
void	handle_heredoc(t_command *cmd);
int		check_heredoc(t_command *cmd_list);

//signals
void	handle_sigint(int sig);
void	setup_parent_signals(void);
void	setup_child_signals(void);

//builtins
void	free_tab(char **tab, int limit);
int		is_valid_identifier(const char *str);
int		cd_builtin(char **args, char **envp);
int		echo_builtin(char **args);
int		env_builtin(t_data *data);
int		exit_builtin(char **args, t_data *data);
int		no_args_export(t_data *data);
int		export_builtin(char **args, t_data *data);
int		pwd_builtin(char **args);
int		unset_builtin(char **args, t_data *data);

#endif