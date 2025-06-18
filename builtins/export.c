/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:34 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 17:50:18 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_args_export(t_data *data)
{
	int		i;
	int		name_len;
	char	*equal_sign;

	i = 0;
	while (data->envp[i])
	{
		equal_sign = ft_strchr(data->envp[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - data->envp[i];
			printf("declare -x %. *s=\"%s\"\n", name_len, data->envp[i],
				equal_sign + 1);
		}
		else
			printf("declare -x %s\n", data->envp[i]);
		i++;
	}
	return (0);
}

/*
**no_args_export:
*/