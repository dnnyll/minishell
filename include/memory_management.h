#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

typedef struct s_command t_command;
typedef struct s_data t_data;
typedef struct s_token t_token;
typedef struct s_lexer_result t_lexer_result;


//	free_commands.c
void	free_string(char **str);
void	free_command_fields(t_command *cmd);
void	free_commands(t_data *data);

//	free_exit.c
void	free_on_exit(t_data *data);

//	free_functions.c
void	free_char_array(char **array);

//	free_lexer.c
void	free_lexer_result(t_lexer_result *result);
void	free_single_token(t_token *token);

#endif