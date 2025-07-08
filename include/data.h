#ifndef DATA_H
# define DATA_H

//	we are linking the structures to our data stucture?!?!?!
typedef struct s_token t_token;
typedef struct s_command t_command;
typedef struct s_env t_env;
typedef struct s_variables t_variables;

typedef	struct	s_data
{
	t_token		*token_head;			//	lexer output (head of list of tokens)
	t_command	*command_head;			//	parser output (head of list of commands)
	t_variables	*variables_head;		//	for new variable assignment ($MYVAR=cake)
	char		**environment_variables;//	stores a copy of the environment
	int			last_exit_code_status;	//	tracks the return code of each command 
										//	it's used to track and support '$?'
	t_env		*env;
	//	not used yet, might not be necessary
	int			pipe_count;				// new - temporary
	int			command_count;			// new - temporary
}	t_data;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
//key : the name of the variable
//value : valu of the variable
//ptr to the next variable

#endif