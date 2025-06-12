/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:22:27 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/09 14:54:43 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef DATA_H
# define DATA_H

typedef struct s_token t_token;
typedef struct s_command t_command;

typedef	struct	s_data
{
	t_token		*token_head;	// lexer output (head of list of tokens)
	t_command	*command_head;	// parser output (head of list of commands)
}	t_data;

#endif