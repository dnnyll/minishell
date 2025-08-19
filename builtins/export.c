/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:20:04 by marjorie          #+#    #+#             */
/*   Updated: 2025/08/19 17:03:12 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_nodes(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	fill_env_array(t_env *env, char **array)
{
	int		i;
	char	*join;

	i = 0;
	while (env)
	{
		if (env->value)
			join = ft_strjoin("=", env->value);
		else
			join = ft_strdup("");
		array[i] = ft_strjoin(env->key, join);
		free(join);
		env = env->next;
		i++;
	}
	array[i] = NULL;
}

char	**env_list_to_array(t_env *env)
{
	char	**array;
	int		count;

	count = count_env_nodes(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	fill_env_array(env, array);
	return (array);
}

void	print_env_head(t_env *head)
{
	int		count;
	int		i;
	t_env	**array;

	count = env_list_size(head);
	array = malloc(sizeof(t_env *) * count);
	if (!array)
		return ;
	i = 0;
	while (head)
	{
		array[i++] = head;
		head = head->next;
	}
	qsort(array, count, sizeof(t_env *), compare_env);
	i = 0;
	while (i < count)
	{
		if (array[i]->value)
			printf("declare -x %s=\"%s\"\n", array[i]->key, array[i]->value);
		else
			printf("declare -x %s\n", array[i]->key);
		i++;
	}
	free(array);
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
	data->last_exit_code_status = 0;
	while (args[i])
	{
		process_export_arg(data, args[i]);
		i++;
	}
    if (data->environment_var)
		free_char_array(data->environment_var);
	data->environment_var = env_list_to_array(data->env_head);
	return (data->last_exit_code_status);
}
