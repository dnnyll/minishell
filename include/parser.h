/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/05 14:33:19 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_redirect
{
	char 				*file;		//	rederection target (filename)
	int					type;		//	type: input/output, append, heredoc
	struct s_redirect	*next;		//	for multiple redirections
} t_redirect;

typedef struct s_command
{
	char				**argv;		//	arguments array (command + args)
	t_redirect			*redir_in;	//	for input redirection (if any)
	t_redirect			*redir_out;	//	for output redirection (if any)
	struct s_command	*next;		//	next command in a pipeline
}s_command;

//	parser
int		count_nodes(t_token	result);
char	**alloc_argv(char **argv, int size);
void	**argument_fill(char **argv, t_token result);
void	argument_collector(t_token result, char **argv);

#endif