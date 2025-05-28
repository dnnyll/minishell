/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:03:43 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 10:28:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	TOKEN_WORD,					// general word or command name
	TOKEN_PIPE,					// |
	TOKEN_REDIR_IN,				// <
	TOKEN_REDIR_OUT,			// >
	TOKEN_HEREDOC,				// <<
	TOKEN_APPEND,				// >>
	TOKEN_EOF,					// end of input (optional)
	TOKEN_ERROR					// for syntax errors or invalid tokens
}	t_token_type;

typedef struct s_token
{
	char			*value;		// actual string, e.g., "ls", "|", ">"
	t_token_type	type; 		// type from the enum above
	struct s_token	*next;		// pointer to the next token
}	t_token;

//	tokens
void	add_token(t_token **list, t_token *new_token);
t_token	*create_token(const char *value, t_token_type type);
void	free_token_list(t_token *token);

#endif