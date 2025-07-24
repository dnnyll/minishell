#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir t_redir;      // Forward declaration
typedef struct s_heredoc t_heredoc;  // Forward declaration
typedef enum e_token_type t_token_type; // Forward declaration if it's an enum


// typedef struct s_redirect
// {
// 	char 				*file;		//	rederection target (filename)
// 	int					type;		//	type: REDIR_IN/OUT, append, heredoc
// 	struct s_redirect	*next;		//	for multiple redirections
// } t_redirect;

typedef struct s_command
{
	t_heredoc			*heredoc_head;		// <--- Link to heredoc manager
	char				**argv;				// NULL-terminated array of arguments (argv[0] = command)
	char				*infile;			// Input redirection file (for '<')
	char				*outfile;			// Output redirection file (for '>' or '>>')
	char				*path;
	char				*value;
	int					append;				// 1 if '>>' (append mode), 0 if '>' (truncate)
	char				*heredoc_delim;		// Delimiter for heredoc (if '<<' is used)
	int					heredoc_quoted;		// Flags heredoc if between single/double quotes.  (<< "EOF" or << 'EOF')
	int					fd_in;				// File descriptor for input (defaults to STDIN_FILENO)
	int					fd_out;				// File descriptor for output (defaults to STDOUT_FILENO)
	struct s_command	*next;				// Pointer to the next command (for pipelines)
	struct s_command	*prev;
	t_token_type		type;
	t_redir				*redir_head;
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
void		parse_commands(t_data *data, t_token *tokens);
t_command	*init_command(void);
void		add_command_to_data(t_command **head, t_command *init_command);
void		parse_commands(t_data *data, t_token *tokens);

//	parser_fill_commands
void	free_commands(t_data *data);
int		count_arguments(t_token *start, t_token *end);
char	**allocate_command_argv(int argc);
void	fill_argv(t_command *command, t_token *start, t_token *end);
void	fill_command_segment(t_command *command, t_token *start, t_token *end);

//	parser_redirect_handling
int		is_redirection(int type);
void	handle_redirections(t_command *command, t_token *start, t_token *end);

//	parser_pipes_handling
void	handle_pipes(t_data *data, t_token *start, t_token *end);

//	parser_variable_handling
char	*ft_strjoin_char(char *input, char c);
char	*handle_exit_code(t_data *data, char *input);
char	*handle_environment_variables(const char *input, int	*i, t_data *data, char * result);
char	*expand_variables(const char *input, t_data *data);
int		isexpandable_variable(const char *str);
void	handle_variables(t_token *tokens);
char	*process_variables(const char *input, t_data *data, t_token *tokens);

//	parser_syntax
t_token	*get_last_token(t_token *head);
int		verify_pipes(t_token *tokens);
int		verify_redirections(t_token *tokens);
int		validate_syntax(t_token *tokens);

#endif