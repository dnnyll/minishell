/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:03:43 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/19 14:26:28 by daniefe2         ###   ########.fr       */
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
	WORD,					// general word or command name (before parsing)
	CMD,					//	comands: echo, ls, etc
	PIPE,					// The pipe character '|'
	REDIR_IN,				// Input redirection: '<'
	REDIR_OUT,				// Output redirection: '>'
	APPEND,					// Append output: '>>'
	HEREDOC,				// Heredoc input: '<<'
	T_EOF,					// end of input (optional)
	ERROR,					// for syntax errors or invalid tokens
	ENV
}	t_token_type;

//	contains information after lexer has been applied
//	we will use this for the parsing part

typedef struct s_token {
	char			*value;			// Actual text (e.g., "echo", "|", "file")
	t_token_type	type;			// What kind of token it is (WORD, PIPE, REDIR_OUT, etc.)
	t_quote_type	quote;			// Quote context (NO_QUOTE, SINGLE_QUOTE, etc.)
	struct s_token	*next;			// Pointer to the next token node
}	t_token;

//	tokens
const char	*token_type_str(t_token_type type);
const char	*quote_type_str(t_quote_type quote);
void		add_token(t_token **list, t_token *new_token);
t_token		*create_token(const char *value, t_token_type type);
void		free_token_list(t_token *token);

#endif