
#include "minishell.h"

#ifndef EXECUTOR_H
# define EXECUTOR_H

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

//commands utils
int		is_command(t_command *cmd);
int		is_redir(t_command *cmd);
int		is_pipe(t_command *cmd);

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
void	free_tab(char **tab, int limit);
int		is_valid_identifier(const char *str);
bool	is_n_flag(char *arg);
bool	is_builtin(t_command **argv);
void	print_error(char *prefix, char *arg, char *suffix);
int		cd_builtin(char **args, t_data *data);
int		echo_builtin(char **args);
int		env_builtin(t_data *data);
int		exit_builtin(char **args, t_data *data);
int		no_args_export(t_data *data);
int		export_builtin(char **args, t_data *data);
int		pwd_builtin(char **args);
int		unset_builtin(char **args, t_data *data);

#endif