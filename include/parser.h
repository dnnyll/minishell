/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/09 14:43:36 by daniefe2         ###   ########.fr       */
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


//	parse_commands
void	parse_commands(t_data *data, t_token *tokens);

#endif