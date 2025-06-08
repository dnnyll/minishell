/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:22:27 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/08 15:31:22 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef DATA_H
# define DATA_H

typedef struct s_token t_token;
typedef struct s_command t_command;

typedef	struct	s_data
{
	t_token		*token_head;
	t_command	*command_head;
}	t_data;

#endif