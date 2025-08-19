/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:46:05 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/19 17:05:35 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		update_env_node(t_env *current, char *key, char *value);
void	add_env_node_exp(t_data *data, char *key, char *value);
void	add_or_update_env_head(t_data *data, char *key, char *value);
void	print_env_head(t_env *head);
void	process_export_arg(t_data *data, char *arg);
char	**env_list_to_array(t_env *env);
int     env_list_size(t_env *head);
int     compare_env(const void *a, const void *b);
int		export_builtin(char **args, t_data *data);

//redirections and pipe
int		setup_redirection(t_command *command, t_data *data);
int		open_input_redir(t_command *command, t_data *data);
int		open_output_redir(t_command *command, t_data *data);
void	close_redirections(t_command *command);
int		ft_pipe(t_command *cmd, int *fd);
int		ft_fork(pid_t *pid, int prev_fd, int *fd);
int		edit_pipe_fd(t_command *cmd, int prev_fd, int *fd, t_data *data);
int		handle_input_redirs(t_command *cmd, int prev_fd, t_data *data);
int		handle_output_redirs(t_command	*cmd, int *fd, t_data *data);

//execution
void	child_process(t_command *cmd, int prev_fd, int *fd, t_data *data);
int		parent_process(int prev_fd, int *fd, pid_t pid, t_data *data);
void	execute_single_builtin(t_command *cmd, t_data *data);
void	execute_buitlins(t_command *cmd, t_data *data);
void	execute_commands(t_command *cmd_list, t_data *data);
void	execute_pipeline(t_command *cdm_list, t_data *data);
void	wait_for_child(pid_t last_pid, t_data *data);
void	exit_child(t_data **data, int status);
void	skip_empty_args(t_command *cmd, t_data *data, int *j);
void	copy_non_empty_args(t_command *cmd, t_data *data, int j);
char	*resolve_command_path(t_command *cmd, t_data *data);
char	*find_path_var(t_data *data);
void	handle_null_path(t_command *cmd, t_data *data, char *path_var);
void	check_directory(char *path, t_command *cmd, t_data *data);
void	check_file_access(char *path, t_command *cmd, t_data *data);

// path utils
char	*find_path_variable(char **envp);
char	*try_paths(char **paths, char *cmd_name);
char	*get_path(char *cmd_name, char **envp);
void	free_split(char **tab);

//signals
extern volatile sig_atomic_t	g_signal_status;
void	handle_sigint(int sig);
void	setup_parent_signals(void);
void	setup_child_signals(void);
void	child_exit_code(int status, t_data *data);

//builtins
int		is_long_limit(const char *str);
void	free_tab(char **tab, int limit);
int		is_valid_identifier(const char *str);
bool	is_n_flag(char *arg);
bool	is_builtin(t_command **argv);
void	print_error(char *prefix, char *arg, char *suffix);
int		cd_builtin(char **args, t_data *data);
int		echo_builtin(char **args);
int		env_builtin(t_data *data);
int		exit_builtin(char **args, t_data *data);
int		pwd_builtin(char **args);
int		unset_builtin(char **args, t_data *data);

#endif