/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:29:13 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:29:15 by daniefe2         ###   ########.fr       */
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
	UNASSIGNED,
	WORD,					// general word or command name (before parsing)
	CMD,					//	comands: echo, ls, etc
	PIPE,					// The pipe character '|'
	REDIR_IN,				// Input redirection: '<'
	REDIR_OUT,				// Output redirection: '>'
	APPEND,					// Append output: '>>'
	HEREDOC,				// Heredoc input: '<<'
	ERROR,					// for syntax errors or invalid tokens
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_quote_type	quote;
	int				expandable;
	struct s_token	*next;
}	t_token;

//	tokens
void		free_tokens(t_data *data);
const char	*token_type_str(t_token_type type);
void		add_token(t_token **list, t_token *new_token);
t_token		*create_token(const char *value, t_token_type type);
void		free_token_list(t_token *token);

//	tokens_expand
void		expand_token_values(t_token *tokens, t_data *data);

#endif