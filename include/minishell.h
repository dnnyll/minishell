/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:28:31 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/19 22:06:08 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	authosized standard libraries
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
# include <limits.h>
# include <dirent.h>
# include <errno.h>

//	personal library/header files
# include "../include/data.h"
# include "../include/tokens.h"
# include "../lib/Libft/libft.h"
# include "../include/lexer.h"
# include "../include/executor.h"
# include "../include/parser.h"
# include "../include/environment_management.h"
# include "../include/heredoc.h"
# include "../include/memory_management.h"

//	init_data.c
t_data		*init_data(void);
t_command	*init_command(void);
t_heredoc	*init_heredoc(int counter);
t_env		*init_env_node(void);
t_token		*init_token(void);

//	process_input.c
void		process_input(char *line, t_data *data);

//	prompt default
# define PROMPT "minishell$ "

#endif