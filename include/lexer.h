#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/*
	helper struct that temporarily holds the result of a token extraction
	to help the lexer keep track of where it is and what it just parsed.
	
	saves the extracted input strings directly to t_tokens struc in tokens.h
	saves the index end position of every string.
*/
typedef struct s_lexer_result
{
	t_token	*token;		//	the string is stored in tokens.h's structure
	int		index;		//	the index position of the input string's end
}	t_lexer_result;

//	extract_word.c
const char *quote_type_str(t_quote_type quote);
int				is_operator_char(char c);
int				get_word_length(const char *input);
t_lexer_result	extract_word(const char *input, int i);

//	extract_quoted.c
int				get_quoted_length(const char *input, char quote_char);
char			*extract_quoted_value(const char *input, int len);
t_lexer_result	extract_quoted(const char *input, int i);

//	extract_operator.c
int				get_operator_length(t_token_type type);
t_token_type	get_operator_type(const char *input);
t_lexer_result	extract_operator(const char *input, int i);

//	lexer.c
int	ft_isspace(int c);
int	is_quote(char c);
int	is_operator_start(char c);
t_lexer_result	extract_token(const char *input, int i);
void	*lexer(t_data *data, const char *input);





void	free_lexer_result(t_lexer_result *result);
void	free_single_token(t_token *token);



#endif
