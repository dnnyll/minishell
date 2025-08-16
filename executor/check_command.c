#include "minishell.h"

char	*resolve_command_path(t_command *cmd, t_data *data)
{
	char	*path;
	char	*path_var;
	int		i;

	if (ft_strchr(cmd->argv[0], '/'))
		return (ft_strdup(cmd->argv[0]));
	path = get_path(cmd->argv[0], data->environment_var);
	if (!path)
	{
		path_var = NULL;
		i = 0;
		while (data->environment_var && data->environment_var[i])
		{
			if (ft_strncmp(data->environment_var[i], "PATH=", 5) == 0)
				path_var = data->environment_var[i] + 5;
			i++;
		}
		if (!path_var || path_var[0] == '\0')
			print_error("minishell: ", cmd->argv[0], ": No such file or directory\n");
		else
			print_error("minishell: ", cmd->argv[0], ": command not found\n");
		exit_child(&data, 127);
	}
	return (path);
}

void	check_command_validity(char *path, t_command *cmd, t_data *data)
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
	if (access(path, F_OK) != 0)
	{
		print_error("minishell: ", cmd->argv[0], ": No such file or directory\n");
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
