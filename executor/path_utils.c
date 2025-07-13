/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:50:49 by mrosset           #+#    #+#             */
/*   Updated: 2025/06/05 11:21:58 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*try_paths(char **paths, char *cmd_name)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd_name, char **envp)
{
	char	*path_line;
	char	**paths;
	char	*cmd_path;

	if (ft_strchr(cmd_name, '/') && access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	path_line = find_path_variable(envp);
	if (!path_line)
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (NULL);
	cmd_path = try_paths(paths, cmd_name);
	free_split(paths);
	return (cmd_path);
}

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
**envp is an array containing  all the environment variables.
**find_path_variable : this function itarate through envp. If a string
	begining with "PATH=" is found, the function return a ptr to the rest
	of the string ("bin:/usr/bin:/sbin...").
**try_paths : this function is for find the exact path of a command. It
	test few repertories to find the good one. It check the accessibility
	with access(). It spilt all cmd to check it separatly with temp and then
	connect all together separate with '/'. It recive an array with all cmd.
**get_path : this function is for find the complet and executable path of a
	command. First it check if the validity of the command, if it's in envp.
	The split the PATH string into an array. Call try_paths() to test all
	repertories.
**free_tab : this function is for properly free the memory of the string
	array returned by ft_split.
*/