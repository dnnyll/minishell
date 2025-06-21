/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:34 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/21 20:05:48 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_args_export(t_data *data)
{
	int		i;
	int		name_len;
	char	*equal_sign;

	i = 0;
	while (data->environment[i])
	{
		equal_sign = ft_strchr(data->environment[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - data->environment[i];
			printf("declare -x %.*s=\"%s\"\n", name_len, data->environment[i],
				equal_sign + 1);
		}
		else
			printf("declare -x %s\n", data->environment[i]);
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
	while (data->environment[i])
	{
		if (ft_strncmp(data->environment[i], name, len) == 0
			&& data->environment[i][len] == '=')
		{
			free(data->environment[i]);
			data->environment[i] = ft_strdup(arg);
			free(name);
			return ;
		}
		i++;
	}
	data->environment = append_env_entry(data->environment, arg);
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
	data->environment[i]' calculates the length of the name.
	And with 'printf("declare -x %.*s=\"%s\"\n"...' displays the name and value
	in quotes.
**declare -x: do like bash, it's just text before declaration.
**%.*s: print a string(%s) with a len given(.*) with name_len, this is only
	for the name before the '='.
**=\"%s\" : print a '=' and then the value between the ""
**is_valid_identifier:
**append_env_entry:
**add_or_update_env:
**export_builtin:
*/