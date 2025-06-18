/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/17 18:16:51 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// typedef struct s_redirect
// {
// 	char 				*file;		//	rederection target (filename)
// 	int					type;		//	type: REDIR_IN/OUT, append, heredoc
// 	struct s_redirect	*next;		//	for multiple redirections
// } t_redirect;

typedef struct s_command
{
	char				**argv;				// NULL-terminated array of arguments (argv[0] = command)
	char				*infile;			// Input redirection file (for '<')
	char				*outfile;			// Output redirection file (for '>' or '>>')
	int					append;				// 1 if '>>' (append mode), 0 if '>' (truncate)
	char				*heredoc_delim;		// Delimiter for heredoc (if '<<' is used)
	int					fd_in;				// File descriptor for input (defaults to STDIN_FILENO)
	int					fd_out;				// File descriptor for output (defaults to STDOUT_FILENO)
	int					is_builtin;			// 1 if the command is a builtin (optional for execution)
	struct s_command	*next;				// Pointer to the next command (for pipelines)
}	t_command;

/*
	information concerning: command
	
	Purpose: stores the arguments that will be passed to execve().

	For: echo hello

	argv = ["echo", "hello", NULL]

	Without this, you cannot run the command.
	The execve() system call literally receives argv as input.

	That's why you collect tokens from `segment_start` to the PIPE position.
	Everything before the pipe belongs to this command.
*/

//	parse_commands
void	parse_commands(t_data *data, t_token *tokens);
t_command	*new_command(void);
void	add_command_to_data(t_command **head, t_command *new_command);
void	parse_commands(t_data *data, t_token *tokens);

//	parser_fill_commands
void free_commands(t_data *data);
int	count_arguments(t_token *start, t_token *end);
char **allocate_command_argv(int argc);
void	fill_argv(t_command *command, t_token *start, t_token *end);
void fill_command_segment(t_command *command, t_token *start, t_token *end);

//	parser_redirect_handling
int		is_redirection(int type);
void	handle_redirections(t_command *command, t_token *start, t_token *end);

//	parser_pipes_handling
void	handle_pipes(t_data *data, t_token *start, t_token *end);

#endif