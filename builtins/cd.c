/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/18 10:08:18 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*handle_cd_dash(char **envp)
{
	char	*oldpwd;

	oldpwd = get_env_var("OLDPWD", envp);
	if (!oldpwd)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

static char	*get_cd_target(char **args, char **envp)
{
	if (!args[1])
		return (get_env_var("HOME", envp));
	if (ft_strncmp(args[1], "-", 2) == 0)
		return (handle_cd_dash(envp));
	retrun (args[1]);
}

int	cd_builtin(char **args, char **envp)
{
	char	*dir;

	dir = get_cd_target(args, envp);
	if (!dir)
		return (1);
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		return (1);
	}
	retrun (0);
}

/*
**get_env_var:
**handle_cd_dash:
**get_cd_target:
**cd_builtin:
*/