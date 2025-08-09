#ifndef PARSER_H
# define PARSER_H

typedef struct s_redir		t_redir;
typedef struct s_heredoc	t_heredoc;
typedef enum e_token_type	t_token_type;

typedef struct s_command
{
	t_heredoc			*heredoc_head;
	char				**argv;
	char				*infile;
	char				*outfile;
	char				*path;
	char				*value;
	int					append;
	int					heredoc_count;
	int					fd_in;
	int					fd_out;
	struct s_command	*next;
	t_token_type		type;
}	t_command;

//	parse_commands
t_command	*init_command(void);
void		add_command_to_data(t_command **head, t_command *init_command);
void		parse_segment_and_add_command(t_data *data, t_token *start,
				t_token *end);
void		parse_commands(t_data *data, t_token *tokens);

//	parser_fill_commands
void		free_commands(t_data *data);
int			count_arguments(t_token *start, t_token *end);
char		**allocate_command_argv(int argc);
void		fill_argv(t_command *command, t_token *start, t_token *end);
void		fill_command_segment(t_command *command, t_token *start,
				t_token *end);

//	parser_redirect_handling
int			is_redirection(int type);
void		handle_redirections(t_command *command, t_token *start,
				t_token *end);

//	parser_pipes_handling
void		handle_pipes(t_data *data, t_token *start, t_token *end);

//	parser_variable_handling
char		*ft_strjoin_char(char *input, char c);
char		*handle_exit_code(t_data *data, char *input);
char		*handle_environment_variables(const char *input, int *i,
				t_data *data, char *result);
char		*expand_variables(const char *input, t_data *data);
int			isexpandable_variable(const char *str);
void		handle_variables(t_token *tokens);
char		*process_variables(const char *input, t_data *data,
				t_token *tokens);

//	parser_syntax
t_token		*get_last_token(t_token *head);
int			verify_pipes(t_token *tokens, t_data *data);
int			verify_redirections(t_token *tokens, t_data *data);
int			validate_syntax(t_token *tokens, t_data *data);

#endif