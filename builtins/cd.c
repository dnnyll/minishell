/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:08 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/17 17:16:32 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
