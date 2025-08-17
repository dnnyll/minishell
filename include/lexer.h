/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:28:15 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:28:18 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
	helper struct that temporarily holds the result of a token extraction
	to help the lexer keep track of where it is and what it just parsed.
	
	saves the extracted input strings directly to t_tokens struc in tokens.h
	saves the index end position of every string.
*/
typedef struct s_lexer_result
{
	t_token	*token;
	int		index;
}	t_lexer_result;

typedef struct s_quote
{
	char	value;
	int		is_quoted;
}	t_quote;

//	extract_word.c
const char		*quote_type_str(t_quote_type quote);

//	lexer_quotes.c
void			init_quote(t_quote *q);
int				handle_quote(const char *input, int *j, char *buffer,
					t_quote *q);
void			set_token_quote(t_token *token, t_quote *q);

//	lexer.c
int				fill_token_buffer(const char *input, int *j, char *buffer,
					t_quote *q);
t_lexer_result	extract_token(const char *input, int i);
int				handle_operator(t_data *data, const char *input, int *i);
int				handle_token(t_data *data, const char *input, int *i);
void			*lexer(t_data *data, const char *input);

//	lexer_utils.c
int				ft_isspace(int c);
int				is_quote(char c);
int				is_operator_start(char c);
int				verify_operator_type(const char *input, int i,
					t_token_type *type);

#endif