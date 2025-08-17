/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:34 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/17 18:29:42 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_node(t_env *current, char *key, char *value)
{
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& current->key[ft_strlen(key)] == '\0')
		{
			free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_env_node_exp(t_data *data, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;

	if (!data->env_head)
		data->env_head = new_node;
	else
	{
		current = data->env_head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	add_or_update_env_head(t_data *data, char *key, char *value)
{
	if (update_env_node(data->env_head, key, value) == 0)
		add_env_node_exp(data, key, value);
}

// maybe this functions is going to be deleted
void	print_env_head(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->value)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

void	process_export_arg(t_data *data, char *arg)
{
	char	*equal_sign;
	char	*key;
	char	*value;

	equal_sign = ft_strchr(arg, '=');
	value = NULL;
	if (equal_sign)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
		key = ft_strdup(arg);

	add_or_update_env_head(data, key, value);

	free(key);
	if (value)
		free(value);
}

int	export_builtin(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		print_env_head(data->env_head);
		return (0);
	}

	while (args[i])
	{
		process_export_arg(data, args[i]);
		i++;
	}
	return (0);
}
