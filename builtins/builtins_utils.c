/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:23:46 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/25 12:04:02 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab, int limit)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i] && (limit == -1 || i < limit))
		free(tab[i++]);
	free(tab);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
**free_tab: Frees an array of string (char** type), if 'limit' is -1, frees
	the entire array up to NULL, else frees only up to 'limit' index.
**is_valid_identifier: checks if s string is a valid identifier for an env
	variable. A valid identifier begins with a letter or an underscore, then can
	contain letters, numbers or underscores up to the '=' sign or the end of the
	string.
*/