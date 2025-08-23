/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_shlvl.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:26:05 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/23 14:34:20 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	is_numeric(const char *str)
// {
// 	int i = 0;
// 	if (!str || str[0] == '\0')
// 		return false;
// 	if (str[0] == '+' || str[0] == '-')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return false;
// 		i++;
// 	}
// 	return true;
// }

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

void increment_shlvl(t_env *env_head)
{
	t_env *current = env_head;
	int shlvl;

	while (current)
	{
		if (ft_strncmp(current->key, "SHLVL", 5) == 0)
		{
			if (!is_numeric(current->value))
				shlvl = 0;
			else
				shlvl = ft_atoi(current->value);

			shlvl++;
			free(current->value);
			current->value = ft_itoa(shlvl);
			return;
		}
		current = current->next;
	}
}
