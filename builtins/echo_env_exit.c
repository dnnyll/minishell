/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:46:44 by marjorie          #+#    #+#             */
/*   Updated: 2025/08/17 18:31:39 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_env	*current;

	if (!data->env_head)
		return (1);
	current = data->env_head;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_data *data)
{
	long	exit_code;

	write(1, "exit\n", 5);
	if (!args[1])
	{
		exit_code = data->last_exit_code_status;
		free_data_list(&data);
		exit(exit_code);
	}
	if (!is_numeric(args[1]) || !is_long_limit(args[1]))
	{
		print_error("minishell: exit: ", args[1],
			": numeric argument required\n");
		free_data_list(&data);
		exit(2);
	}
	if (args[2])
		return (print_error("minishell: exit: too many arguments\n",
				NULL, NULL), 1);
	exit_code = ft_atoi(args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	free_data_list(&data);
	exit(exit_code);
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
**is_numeric: Checks if the given string is a valid int, accept an optional
	sign (+ or -). Checks that the following chars are digits and return 1
	if it's a number or 0.
**exit_builtin: This function handles the exit command. prints "exit" on the
	error output, without args exit exits with code 0. With non numeric args
	displays an error and exits with code 2. With multiple args displays an
	error and returns 1 but doesn't exit. With a sigle arg use atoi to convert
	it and ensure that the code is between 0 and 255 and exit with this code.
**256: a process return always a number between 0 and 255 (unsigned int sur
	8 bits).
**Test: run minishell in a terminal, cmd exit 42 and then echo $?
*/