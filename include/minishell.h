/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:19:49 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 13:56:09 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/06/13 14:44:25 by daniefe2         ###   ########.fr       */
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
# include <stdbool.h>
# include "data.h"
# include "tokens.h"
# include "../lib/Libft/libft.h"
# include "lexer.h"
# include "executor.h"
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
// void print_redirections(t_redirect *redir, const char *label);
void print_commands(t_command *cmd_list);
void print_single_command(t_command *cmd);
void print_data(t_data *data);
void print_tokens(t_data *data);
void debug_parser_output(t_data *data);
void print_commands(t_command *cmd);

//	main.c (to be re-arranged)
const char *token_type_str(t_token_type type);
const char *quote_type_str(t_quote_type quote);
void	free_tokens(t_data *data);
// void	free_commands(t_data *data);




//	prompt default
# define PROMPT "minishell$ "



#endif