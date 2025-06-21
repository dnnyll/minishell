/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:23 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/21 18:33:23 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (0);
}
/*
**env: displays all env variables as NAME=VALUE pairs.
**env_buitlin: Displays all available env variables in the t_data struct, in
	the KEY=VALUE format. Iterate through the linked list data, for each
	element if the variable has a value, it is display with the format
	key=value\n. Use write to display to standard output and always return 0
	to indicate sucess.
*/