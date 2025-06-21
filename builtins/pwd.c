/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:50:41 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/21 20:02:34 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **args)
{
	char	*cwd;

	if (args[1])
	{
		printf("pwd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

/*
**pwd_builtin: displays the absolute path of the current directory, follow by
	a new line. This funtion work for the command "pwd" only.
**cwd: current working directory
**getcwd: If we pass NULL as the first arg and 0 as the 2nd, it automatically
	allocates memory to store the current directory path.
*/