/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:03:43 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/08 15:01:39 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef enum e_token_type
{
	WORD,					// general word or command name
	CMD,					//	comands: echo, ls, etc
	PIPE,					// |
	REDIR_IN,				// <
	REDIR_OUT,				// >
	HEREDOC,				// <<
	APPEND,					// >>
	T_EOF,					// end of input (optional)
	ERROR,					// for syntax errors or invalid tokens
	ENV
}	t_token_type;

//	contains information after lexer has been applied
//	we will use this for the parsing part

typedef struct s_token
{
	char			*value;		// actual string, e.g., "ls", "|", ">"
	t_token_type	type; 		// type from the enum above
	struct s_token	*next;		// pointer to the next token
	t_quote_type	quote;
}	t_token;

// data:

// typedef struct s_data
// {
// 	t_token		tokens;
// }				t_data;

//	tokens
void	add_token(t_token **list, t_token *new_token);
t_token	*create_token(const char *value, t_token_type type);
void	free_token_list(t_token *token);

#endif