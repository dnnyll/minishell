/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:25:52 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:25:58 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_list_env_value(t_env *env_head, const char *name)
	{
	t_env	*current;

	current = env_head;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	add_env_node(t_env **head, t_env *new_node)
{
	t_env	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*create_node(const char *env_var_line)
{
	int		equal_pos;
	t_env	*env;

	env = init_env_node();
	if (!env)
		return (NULL);
	equal_pos = 0;
	while (env_var_line[equal_pos] && env_var_line[equal_pos] != '=')
		equal_pos++;
	if (env_var_line[equal_pos] != '=')
	{
		env->key = ft_strdup(env_var_line);
		env->value = ft_strdup("");
	}
	else
	{
		env->key = ft_substr(env_var_line, 0, equal_pos);
		env->value = ft_substr(env_var_line, equal_pos + 1,
				ft_strlen(env_var_line) - (equal_pos + 1));
	}
	if (!env->key || !env->value)
		return (free_env_node(env), NULL);
	env->next = NULL;
	return (env);
}

t_env	*build_env_list(char **environment_var)
{
	t_env	*head;
	int		i;
	t_env	*node;

	head = NULL;
	i = 0;
	while (environment_var[i])
	{
		node = create_node(environment_var[i]);
		if (!node)
		{
			free_env_list(head);
			return (NULL);
		}
		add_env_node(&head, node);
		i++;
	}
	return (head);
}
