/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:34 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/06 17:57:05 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_args_export(t_data *data)
{
	int		i;
	int		name_len;
	char	*equal_sign;

	i = 0;
	while (data->environment_var[i])
	{
		equal_sign = ft_strchr(data->environment_var[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - data->environment_var[i];
			printf("declare -x %.*s=\"%s\"\n", name_len, data->environment_var[i],
				equal_sign + 1);
		}
		else
			printf("declare -x %s\n", data->environment_var[i]);
		i++;
	}
	return (0);
}

char	**append_env_entry(char **environment, char *new_var)
{
	int		i;
	char	**new_env;

	i = 0;
	while (environment[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (environment);
	i = 0;
	while (environment[i])
	{
		new_env[i] = ft_strdup(environment[i]);
		if (!new_env[i])
			return (free_tab(new_env, i), environment);
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (free_tab(new_env, i), environment);
	new_env[i + 1] = NULL;
	free_tab(environment, -1);
	return (new_env);
}

void	add_or_update_env(t_data *data, char *arg)
{
	int		i;
	int		len;
	char	*name;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	name = ft_substr(arg, 0, len);
	i = 0;
	while (data->environment_var[i])
	{
		if (ft_strncmp(data->environment_var[i], name, len) == 0
			&& data->environment_var[i][len] == '=')
		{
			free(data->environment_var[i]);
			data->environment_var[i] = ft_strdup(arg);
			free(name);
			return ;
		}
		i++;
	}
	data->environment_var = append_env_entry(data->environment_var, arg);
	free(name);
}

int	export_builtin(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("export: '%s': not a valid identifier\n", args[i]);
		else
			add_or_update_env(data, args[i]);
		i++;
	}
	return (0);
}

/*
**no_args_export: This function displays all env variables in a redable
	format by the export command like the bash do. If a variable as a value
	it displays otherwise displays : declare -x VAR. With 'strchr' find the
	'=' that separates name and value. 'name_len = equal_sign -
	data->environment_var[i]' calculates the length of the name.
	And with 'printf("declare -x %.*s=\"%s\"\n"...' displays the name and value
	in quotes.
**declare -x: do like bash, it's just text before declaration.
**%.*s: print a string(%s) with a len given(.*) with name_len, this is only
	for the name before the '='.
**=\"%s\" : print a '=' and then the value between the ""
**append_env_entry: Duplicates the current env array and appends a new variable.
	Frees the old array and returns the updated one. If memory allocation fails,
	returns the original env.
**add_or_update_env: Checks if the variable already exists int ht env. If found,
	replaces it with the new value. If not, appends the new variable using
	append_env_entry.
**export_builtin: Handles the export builtins with args. For each valid
	identifier, adds or updates the variable in the env. Prints an error message
	if the identifier is invalid.
*/