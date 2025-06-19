/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:29 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 17:14:07 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(char **args, t_data *data)
{
	int	exit_code;

	(void)data;
	write(2, "exit\n", 5);
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]))
	{
		write(2, "exit: numeric argument required\n", 32);
		exit(2);
	}
	if (args[2])
	{
		write(2, "exit: too many arguments\n", 25);
		return (1);
	}
	exit_code = ft_atoi(args[1]) % 256;
	if (exit_code < 0)
		exit_code += 256;
	exit(exit_code);
}

/*
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
*/