/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_and_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 19:23:07 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/06 17:53:49 by daniefe2         ###   ########.fr       */
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

int	env_builtin(t_data *data)
{
	int	i;

	i = 0;
	if (!data->environment_var)
		return (1);
	while (data->environment_var[i])
	{
		printf("%s\n", data->environment_var[i]);
		i++;
	}
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
**env: displays all env variables as NAME=VALUE pairs.
**env_buitlin: Displays all available env variables in the t_data struct, in
	the KEY=VALUE format. Iterate through the linked list data, for each
	element if the variable has a value, it is display with the format
	key=value\n. Use write to display to standard output and always return 0
	to indicate sucess.
*/