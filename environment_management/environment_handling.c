/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:25:41 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 18:57:32 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (data->environment_var[i])
	{
		if (ft_strncmp(data->environment_var[i], variable_name,
				variable_length) == 0
			&& data->environment_var[i][variable_length] == '=')
			return (ft_strdup(data->environment_var[i] + variable_length + 1));
		i++;
	}
	return ("");
}

char	*handle_environment_variables(const char *input,
	int *i, t_data *data, char *result)
{
	int		start;
	char	*variable_name;
	char	*value;
	char	*new_result;

	start = *i;
	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;
	variable_name = ft_substr(input, start, *i - start);
	value = search_env_value(data, variable_name);
	if (!value)
		return (printf("Error: search_env_value not found for the input\n"),
			NULL);
	free(variable_name);
	new_result = ft_strjoin(result, value);
	if (value && value[0] != '\0')
		free(value);
	return (new_result);
}
