/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:23 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 13:50:50 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data)
{
	while (data)
	{
		if (data->value)
		{
			write(1, data->key, ft_strlen(data->key));
			write(1, "=", 1);
			write(1, data->value, ft_strlen(data->value));
			write(1, "\n", 1);
		}
		data = data->next;
	}
	return (0);
}
/*
**env: displays all env variables as NAME=VALUE pairs.
*/