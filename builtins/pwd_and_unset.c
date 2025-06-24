

#include "minishell.h"

int	pwd_builtin(char **args)
{
	char	*cwd;

	if (args[1])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static int	should_remove(char *entry, char *var_name)
{
	size_t	len;

	len = ft_strlen(var_name);
	return (ft_strncmp(entry, var_name, len) == 0 && entry[len] == '=');
}

char	**remove_env_entry(char **environment, char *var_name)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while (environment[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (environment);
	i = -1;
	j = 0;
	while (environment[++i])
	{
		if (!should_remove(environment[i], var_name))
			{
				new_env[j] = ft_strdup(environment[i]);
				if(!new_env[j])
					return (free_tab(new_env, j), environment);
				j++;
			}
	}
	new_env[j] = NULL;
	free_tab(environment, -1);
	return (new_env);
}

int	unset_buitlin(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("unset: '%s': not a valid identifier\n", args[i]);
		else
			data->environment = remove_env_entry(data->environment, args[i]);
		i++;
	}
	return (0);
}

/*
**pwd_builtin: displays the absolute path of the current directory, follow by
	a new line. This funtion work for the command "pwd" only.
**cwd: current working directory
**getcwd: If we pass NULL as the first arg and 0 as the 2nd, it automatically
	allocates memory to store the current directory path.
**should_remove: Calculate the length of var_name, compare this portion with the
	beginning of entry. Checks that the following char is an '=' (to avoid
	deleting variable with the same prefix).
**remove_env_entry: This function is for remove a specific env variable from the
	env. It counts the number of entries in env, allocates a new array. Copies the
	variable except the one to be removed, using should_remove and frees the old
	array.
**unset_builtin: This is the main unset builtin function. It iterates through the
	argsgiven after unset. For each valid name(using is_valid_identifier) calls
	remove_env_entry. Displays an error message if the identifier is invalid.
	Returns 0 in all cases (as expected by the unset builtin in bash).
*/