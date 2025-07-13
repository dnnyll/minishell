
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

//	personal library/header files
# include "data.h"
# include "tokens.h"
# include "../lib/Libft/libft.h"
# include "lexer.h"
# include "executor.h"
# include "parser.h"

//	init_data.c
t_data	init_data(void);

//	environement_handling.c
char	**copy_environment(char **envp);
char	*search_env_value(t_data *data, const char *name);

//	printers.c

// void print_redirections(t_redirect *redir, const char *label);
void	print_commands(t_command *cmd_list);
void	print_single_command(t_command *cmd);
void	print_data(t_data *data);
void	print_tokens(t_data *data);
void	debug_parser_output(t_data *data);
void	print_commands(t_command *cmd);
void	debug_environment_printer(t_data *data);

//	main.c (to be re-arranged)
void	free_tokens(t_data *data);

//	utility_functions
void	free_char_array(char **array);

//	prompt default
# define PROMPT "minishell$ "

#endif