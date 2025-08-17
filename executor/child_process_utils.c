/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:47:34 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/17 10:47:35 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper to resolve command path
char	*resolve_command_path(t_command *cmd, t_data *data)
{
	if (ft_strchr(cmd->argv[0], '/'))
		return (ft_strdup(cmd->argv[0]));
	return (get_path(cmd->argv[0], data->environment_var));
}

// Helper to find PATH environment variable
char	*find_path_var(t_data *data)
{
	int	i;

	i = 0;
	while (data->environment_var && data->environment_var[i])
	{
		if (ft_strncmp(data->environment_var[i], "PATH=", 5) == 0)
			return (data->environment_var[i] + 5);
		i++;
	}
	return (NULL);
}

// Helper to handle path null case
void	handle_null_path(t_command *cmd, t_data *data, char *path_var)
{
	if (!path_var || path_var[0] == '\0')
		print_error("minishell: ", cmd->argv[0], ": No such file or "
			"directory\n");
	else
		print_error("minishell: ", cmd->argv[0], ": command not found\n");
	exit_child(&data, 127);
}
