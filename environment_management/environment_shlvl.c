/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:26:05 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:26:07 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_array(t_data *data)
{
	int		i;
	char	*new_entry;
	t_env	*current;

	current = data->env_head;
	while (current)
	{
		if (ft_strncmp(current->key, "SHLVL", 5) == 0)
		{
			i = 0;
			while (data->environment_var[i])
			{
				if (ft_strncmp(data->environment_var[i], "SHLVL=", 6) == 0)
				{
					new_entry = ft_strjoin("SHLVL=", current->value);
					free(data->environment_var[i]);
					data->environment_var[i] = new_entry;
					return ;
				}
				i++;
			}
		}
		current = current->next;
	}
}

void	increment_shlvl(t_env *env_head)
{
	t_env	*current;
	int		shlvl;

	current = env_head;
	while (current)
	{
		if (ft_strncmp(current->key, "SHLVL", 5) == 0)
		{
			shlvl = ft_atoi(current->value);
			if (shlvl > 0)
				shlvl++;
			free(current->value);
			current->value = ft_itoa(shlvl);
			return ;
		}
		current = current->next;
	}
}
