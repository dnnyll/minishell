/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:58:12 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/08 15:41:49 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	authosized libraries
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>
# include "data.h"
# include "tokens.h"
# include "libft.h"
# include "lexer.h"
# include "parser.h"

/*

//	libraries/directories of programs
# include "input/input.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "executor/executor.h"
# include "env/env.h"
# include "signals/signals.h"
# include "utils/utils.h"
*/

//	init_data.c
t_data	init_data(void);

//	printers.c
void print_redirections(t_redirect *redir, const char *label);
void print_commands(t_data *data);
void print_tokens(t_data *data);

//	main.c (to be re-arranged)
const char *token_type_str(t_token_type type);
const char *quote_type_str(t_quote_type quote);
void	free_tokens(t_data *data);
void	free_commands(t_data *data);




//	prompt default
# define PROMPT "minishell$ "



#endif