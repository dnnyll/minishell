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

bool	is_builtin(t_command **argv)
{
	if (!argv || !*argv || !(*argv)->argv || !(*argv)->argv[0])
		return (false);
	if (ft_strncmp((*argv)->argv[0], "echo", 5) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "cd", 3) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "pwd", 4) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "export", 7) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "unset", 6) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "env", 4) == 0)
		return (true);
	if (ft_strncmp((*argv)->argv[0], "exit", 5) == 0)
		return (true);
	return (false);
}

/*
** is_buitlins : !argv->the cmd ptr is NULL, !*argv->the cmd pointed to is
	NULL, !(*argv)->agv -> the argv array(the cmds argv)doesn't exist, 
	!(*argv)->argv[0]-> there is no cmd(empt line). If any ot htese conditions
	is true, it's not a valid command, so we return false.
	This function is for check if the cmd is a buitlins or not, ft_strncmp
	compare each char of argv[0] and return true if it match.
**free_tab: Frees an array of string (char** type), if 'limit' is -1, frees
	the entire array up to NULL, else frees only up to 'limit' index.
**is_valid_identifier: checks if s string is a valid identifier for an env
	variable. A valid identifier begins with a letter or an underscore, then can
	contain letters, numbers or underscores up to the '=' sign or the end of the
	string.
*/