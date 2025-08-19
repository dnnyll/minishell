/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:30:55 by marjorie          #+#    #+#             */
/*   Updated: 2025/08/19 17:26:01 by marjorie         ###   ########.fr       */
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
	t_env	*current;

	current = data->env_head;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& current->key[ft_strlen(key)] == '\0')
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return ;
		}
		current = current->next;
	}
	add_env_node_exp(data, key, value);
}

int	env_list_size(t_env *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	compare_env(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strncmp(env_a->key, env_b->key, INT_MAX));
}
