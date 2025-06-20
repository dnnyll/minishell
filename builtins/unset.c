/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:46 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/21 20:17:50 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**remove_env_entry(char **environment, const char *name)
{
	int	i;
}

int	unset_buitlin(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
			printf("unset: '%s': not a valid identifier\n", args[i]);
		else
			data->environment = remove_env_entry(data->environment, args[i]);
		i++;
	}
	return (0);
}

/*
**remove_env_entry:
**unset_builtin:
*/