/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:19:49 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/05 10:19:51 by mrosset          ###   ########.fr       */
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
# include "tokens.h"
# include "../lib/Libft/libft.h"
# include "lexer.h"
# include "executor.h"

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


void print_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);



//	prompt default
# define PROMPT "minishell$ "



#endif