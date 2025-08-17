/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:27:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:27:48 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_token		t_token;
typedef struct s_command	t_command;
typedef struct s_env		t_env;
typedef struct s_variables	t_variables;
typedef struct s_heredoc	t_heredoc;
typedef struct s_redir		t_redir;

typedef struct s_data
{
	t_token			*token_head;
	t_command		*command_head;
	t_env			*env_head;
	char			**environment_var;
	int				last_exit_code_status;
	int				pipe_count;
	int				command_count;
}	t_data;

#endif