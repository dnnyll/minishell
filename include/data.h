#ifndef DATA_H
# define DATA_H

//	we are linking the structures to our data stucture?!?!?!
typedef struct s_token t_token;
typedef struct s_command t_command;
typedef struct s_env t_env;
typedef struct s_variables t_variables;
typedef struct s_heredoc t_heredoc;
typedef struct s_redirection t_redirection;

typedef	struct	s_data
{
	t_token		*token_head;			//	lexer output (head of list of tokens)
	t_command	*command_head;			//	parser output (head of list of commands)
	t_variables	*variables_head;		//	for new variable assignment ($MYVAR=cake)
	t_heredoc	*heredoc_head;
	t_redirection	*redirection_head;
	char		**environment_var;//	stores a copy of the environment
	int			last_exit_code_status;	//	tracks the return code of each command 
										//	it's used to track and support '$?'
	t_env		*env_head;	
	int			pipe_count;				// new - temporary
	int			command_count;			// new - temporary
}	t_data;

#endif