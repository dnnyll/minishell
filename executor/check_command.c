/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 10:47:38 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/17 13:26:40 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Helper to skip empty arguments
void	skip_empty_args(t_command *cmd, t_data *data, int *j)
{
	*j = 0;
	while (cmd->argv[*j] && cmd->argv[*j][0] == '\0')
		(*j)++;
	if (!cmd->argv[*j])
		exit_child(&data, 0);
}

// Helper to allocate and copy non-empty arguments
void	copy_non_empty_args(t_command *cmd, t_data *data, int j)
{
	int		k;
	int		i;
	char	**new_argv;

	k = 0;
	while (cmd->argv[j + k])
		k++;
	new_argv = malloc(sizeof(char *) * (k + 1));
	if (!new_argv)
		exit_child(&data, 1);
	i = 0;
	while (cmd->argv[j])
		new_argv[i++] = cmd->argv[j++];
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

// Helper to check if path is a directory
void	check_directory(char *path, t_command *cmd, t_data *data)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		print_error("minishell: ", cmd->argv[0], ": Is a directory\n");
		free(path);
		exit_child(&data, 126);
	}
}

// Helper to check file existence and permissions
void	check_file_access(char *path, t_command *cmd, t_data *data)
{
	if (access(path, F_OK) != 0)
	{
		print_error("minishell: ", cmd->argv[0], ": No such file or "
			"directory\n");
		free(path);
		exit_child(&data, 127);
	}
	if (access(path, X_OK) != 0)
	{
		print_error("minishell: ", cmd->argv[0], ": Permission denied\n");
		free(path);
		exit_child(&data, 126);
	}
}
