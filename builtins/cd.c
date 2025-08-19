/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/08/19 22:00:39 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(char *name, t_data *data)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (data->environment_var[i])
	{
		if (ft_strncmp(data->environment_var[i], name, len) == 0
			&& data->environment_var[i][len] == '=')
			return (data->environment_var[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*handle_cd_dash(t_data *data)
{
	char	*oldpwd;

	oldpwd = get_env_var("OLDPWD", data);
	if (!oldpwd)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

static char	*get_cd_target(char **args, t_data *data)
{
	if (!args[1])
		return (get_env_var("HOME", data));
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_cd_dash(data));
	return (args[1]);
}

/*int	cd_builtin(char **args, t_data *data)
{
	char	*dir;
	int		args_count;

	args_count = 0;
	while (args[args_count])
		args_count++;
	if (args_count > 2)
	{
		data->last_exit_code_status = 1;
		print_error("minishell: cd: ", NULL, "too many arguments\n");
		return (1);
	}
	dir = get_cd_target(args, data);
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}*/
int	cd_builtin(char **args, t_data *data)
{
	char	*dir;
	int		args_count;

	args_count = 0;
	while (args[args_count])
		args_count++;
	if (args_count > 2)
	{
		data->last_exit_code_status = 1;
		print_error("minishell: cd: ", NULL, "too many arguments\n");
		return (1);
	}
	dir = get_cd_target(args, data);
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
	{
		print_error("minishell: cd: ", dir, ": ");
		print_error("", strerror(errno), "\n");
		data->last_exit_code_status = 1;
		return (1);
	}
	data->last_exit_code_status = 0;
	return (0);
}

/*
**get_env_var: Search for an env variable int the envp array. Use strncmp
	to check if the string begins with name=. Return a ptr to the value.
**handle_cd_dash: Handle th cd command which should return to the old
	directory (OLDPWD). Calls get_env_var and if OLDPWD is define, it displays
	and returns it. Otherwise it displays an error.
**get_cd_target: Determines which folder to got to. If cd with no args -> returns
	$HOME, if cd - -> calls handle_cd_dash to return $OLDPWD, else -> returns the
	arg given (args[1]).
**cd_builtin: This is the main function of the cd builtin, gets the target
	directory using get_cd_target, uses chdir() to change directories and
	displays an error message if the operation fails.
** cd cmds : cd → doit te ramener dans le HOME ($HOME).
			cd ~ → équivalent à cd (HOME).
			cd . → reste dans le dossier actuel.
			cd .. → va dans le dossier parent.
			cd / → va à la racine du système.
			cd /home/mrosset/Desktop/minishell → va à l’endroit précisé.
			valgrind --leak-check=full --track-origins=yes ./minishell
*/