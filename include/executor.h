/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:48:45 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/23 10:46:45 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef EXECUTOR_H
# define EXECUTOR_H

//pipe utils
int		ft_pipe(t_command *cmd, int *fd);
int		ft_fork(pid_t *pid, int prev_fd, int *fd);
void	edit_pipe_fd(t_command *cmd, int prev_fd, int *fd);

//execution
void	child_process(t_command *cmd, int prev_fd, int *fd, t_data *data);
int		parent_process(int prev_fd, int *fd);
void	execute_buitlins(t_command *cmd, t_data *data);
void	execute_commands(t_command *cmd_list, t_data *data);
void	execute_pipeline(t_command *cdm_list, t_data *data);

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
char	*expand_line(char *line, t_command *cmd, t_data *data);
void	child_heredoc(t_command *cmd, int *pipe_fd, t_data *data);
void	parent_heredoc(t_command *cmd, int *pipe_fd, int pid);
void	handle_heredoc_sigint(int sig);
void	handle_heredoc(t_command *cmd, t_data *data);
int		check_heredoc(t_command *cmd_list, t_data *data);

//signals
extern volatile sig_atomic_t	g_signal_status;
void	handle_sigint(int sig);
void	setup_parent_signals(void);
void	setup_child_signals(void);

//builtins
void	free_tab(char **tab, int limit);
int		is_valid_identifier(const char *str);
bool	is_builtin(t_command **argv);
int		cd_builtin(char **args, char **envp);
int		echo_builtin(char **args);
int		env_builtin(t_data *data);
int		exit_builtin(char **args, t_data *data);
int		no_args_export(t_data *data);
int		export_builtin(char **args, t_data *data);
int		pwd_builtin(char **args);
int		unset_builtin(char **args, t_data *data);

#endif