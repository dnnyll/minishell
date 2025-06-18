/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:15 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 12:50:14 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	echo_builtin(char **args)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}

/*
**bool: is easier to read with true of false
**is_n_flag: check if the string start with a '-' and a 'n' and if the
	following chars are only 'n', else return false.
**echo_builtin: The principal funtion, ignores the -n flags, printd the
	following args with spaces, only adds a "\n" if no args are found.
	Iterates thougt the args starting from argv[1], as long as if founds
	valid -n flags, it disables line break printing with newline == true.
	Else it prints a '\n'.
*/