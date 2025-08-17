/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:29:25 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:29:26 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof (t_data));
	if (!data)
		return (NULL);
	data->token_head = NULL;
	data->command_head = NULL;
	data->env_head = NULL;
	data->environment_var = NULL;
	data->last_exit_code_status = 0;
	data->pipe_count = 0;
	data->command_count = 0;
	return (data);
}

t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->heredoc_head = NULL;
	command->argv = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->path = NULL;
	command->value = NULL;
	command->append = 0;
	command->heredoc_count = 0;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->next = NULL;
	return (command);
}

t_heredoc	*init_heredoc(int counter)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->filename = NULL;
	heredoc->delimiter = NULL;
	heredoc->index = 0;
	heredoc->quoted = 0;
	heredoc->counter = counter;
	heredoc->pid = getpid();
	heredoc->next = NULL;
	return (heredoc);
}

t_env	*init_env_node(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = NULL;
	token->type = UNASSIGNED;
	token->quote = NO_QUOTE;
	token->expandable = 0;
	token->next = NULL;
	return (token);
}
