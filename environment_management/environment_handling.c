
#include <minishell.h>

char	**copy_environment(char **envp)
{
	int		i;
	char	**environment_copy;

	i = 0;
	while (envp[i])
		i++;
	environment_copy = malloc(sizeof(char *) * (i + 1));
	if (!environment_copy)
		return (perror("Error: alloc environemnt_copy\n"), NULL);
	i = 0;
	while (envp[i])
	{
		environment_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	if (!environment_copy)
		return (perror("Error: copying envp to environment_copy\n"), NULL);
	environment_copy[i] = NULL;
	return (environment_copy);
}

char	*search_env_value(t_data *data, const char *variable_name)
{
	int	i;
	int	variable_length;

	i = 0;
	variable_length = ft_strlen(variable_name);
	if (!data || !variable_name)
		return (perror("Error: empty data or name @ search_env_value\n"), NULL);
	while(data->environment_var[i])
	{
		if (ft_strncmp(data->environment_var[i], variable_name, variable_length) == 0
			&& data->environment_var[i][variable_length] == '=')
				return (ft_strdup(data->environment_var[i] + variable_length + 1));
			i++;
	}
	return("");
}
