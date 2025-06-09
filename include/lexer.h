/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:07:18 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/31 11:47:05 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_token_result
{
	t_token	*token;
	int		new_index;
}	t_token_result;


//	extract_word
int				is_operator_char(char c);
int				get_word_length(const char *input);
t_token_result	extract_word(const char *input, int i);

//	extract_quoted
int				get_quoted_length(const char *input, char quote_char);
char			*extract_quoted_value(const char *input, int len);
t_token_result	extract_quoted(const char *input, int i);

//	extract_operator
int				get_operator_length(t_token_type type);
t_token_type	get_operator_type(const char *input);
t_token_result	extract_operator(const char *input, int i);

//	lexer
int	ft_isspace(int c);
int	is_quote(char c);
int	is_operator_start(char c);
t_token_result	extract_token(const char *input, int i);
t_token	*lexer(const char *input);

#endif
