/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/06 12:18:00 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redirect
{
	char 				*file;		//	rederection target (filename)
	int					type;		//	type: REDIR_IN/OUT, append, heredoc
	struct s_redirect	*next;		//	for multiple redirections
} t_redirect;

typedef struct s_command
{
	char				**argv;		//	arguments array (command + args)
	t_redirect			*redir_in;	//	for input redirection (if any)
	t_redirect			*redir_out;	//	for output redirection (if any)
	struct s_command	*next;		//	next command in a pipeline
}t_command;

//	parser_commands
int	count_nodes(t_token	*head);
char	**alloc_argv(char **argv, int size);
char	**argument_fill(char **argv, t_token *head);
char **argument_collect(t_token *head);

//	parse_redirections
void	append_to_redir_list(t_redirect **list, t_redirect *new_node);
void	detect_redirections(t_token *head, t_command *cmd);

//	parser
t_command	*parse_tokens(t_token *token_list);

#endif