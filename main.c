/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:33:36 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 18:47:29 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*initialize_minishell(char **envp)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (NULL);
	data->environment_var = copy_environment(envp);
	data->env_head = build_env_list(data->environment_var);
	increment_shlvl(data->env_head);
	update_env_array(data);
	return (data);
}

void	handle_exit(t_data *data)
{
	printf("exit\n");
	clear_history();
	rl_clear_history();
	free_data_list(&data);
}

bool	should_skip_line(char *line)
{
	if (line[0] == '\0')
	{
		free(line);
		return (true);
	}
	add_history(line);
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*input_line;

	(void)argc;
	(void)argv;
	data = initialize_minishell(envp);
	if (!data)
		return (1);
	setup_parent_signals();
	while (1)
	{
		if (g_signal_status)
		{
			g_signal_status = 0;
			continue ;
		}
		input_line = readline("minishell> ");
		if (!input_line)
			return (handle_exit(data), 0);
		if (should_skip_line(input_line))
			continue ;
		process_input(input_line, data);
	}
	return (0);
}
