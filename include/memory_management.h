/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:28:23 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:35:41 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

typedef struct s_command		t_command;
typedef struct s_data			t_data;
typedef struct s_token			t_token;
typedef struct s_lexer_result	t_lexer_result;

//	free_commands.c
void	free_command_node(t_command *cmd);
void	*get_next_command(void *node);
void	free_commands(t_data *data);

//	free_data.c
void	free_data_list(t_data **data_ptr);

//	free_env.c
void	free_env_node(t_env *env);
void	free_env_list(t_env *env);

//	free_exit.c
void	free_on_exit(t_data *data);

//	free_functions.c
void	free_char_array(char **array);
void	free_list(void *head, void *(*get_next)(void *),
			void (*free_node)(void *));

//	free_heredocs.c
void	free_heredocs_in_command(t_command *command);

//	free_tokens.c
void	free_token_node(t_token *token);
void	*get_next_token(void *node);
void	free_tokens(t_data *data);
void	free_single_token(t_token *token);
void	free_lexer_result(t_lexer_result *result);

#endif