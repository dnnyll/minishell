
#ifndef MINISHELL_H
# define MINISHELL_H

//	authosized standard libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>

//	personal library/header files
# include "../include/data.h"
# include "../include/tokens.h"
# include "../lib/Libft/libft.h"
# include "../include/lexer.h"
# include "../include/executor.h"
# include "../include/parser.h"
# include "../include/environment_management.h"
# include "../include/heredoc.h"
# include "../include/memory_management.h"

//	init_data.c
t_data		*init_data(void);
t_command	*init_command(void);
// t_redir		*init_redir(void);
t_heredoc	*init_heredoc(int counter);


//	printers.c
// void print_redirections(t_redirect *redir, const char *label);
void	print_commands(t_command *cmd_list);
void	print_single_command(t_command *cmd);
void	print_data(t_data *data);
void	print_tokens(t_data *data);
void	debug_parser_output(t_data *data);
void	print_commands(t_command *cmd);
void	print_env_list(t_env *env);
void	print_data_debug(t_data *data);
void	debug_environment_variables_printer(t_data *data);
void 	print_heredoc(t_heredoc *heredoc);

//	prompt default
# define PROMPT "minishell$ "

#endif