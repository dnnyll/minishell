/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_default.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:56:56 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/23 14:59:32 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_directory(t_data *data, const char *path)
{
	char	*prev;

	prev = getcwd(NULL, 0);
	if (!prev)
		prev = ft_strdup("/");
	if (chdir(path) != 0)
	{
		perror("cd");
		free(prev);
		return ;
	}
	free(data->oldpwd);
	data->oldpwd = prev;
	update_pwd_vars(data);
}

char	**create_default_env(void)
{
	char	**env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("/");
	env = malloc(sizeof(char *) * 5);
	if (!env)
	{
		free(cwd);
		return (NULL);
	}
	env[0] = ft_strjoin("PATH=", "/usr/local/bin:/usr/bin:/bin");
	env[1] = ft_strjoin("PWD=", cwd);
	env[2] = ft_strdup("OLDPWD=");
	env[3] = ft_strdup("SHLVL=1");
	env[4] = NULL;
	free(cwd);
	return (env);
}

t_env	*get_set_nodee(t_data *data, const char *key, const char *value)
{
	t_env	*node;

	node = data->env_head;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key)) == 0)
			return (node);
		node = node->next;
	}
	node = init_env_node();
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	node->next = NULL;
	add_env_node(&data->env_head, node);
	return (node);
}

void	update_pwd_vars(t_data *data)
{
	char	*cwd;
	t_env	*pwd_node;
	t_env	*oldpwd_node;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("/");
	oldpwd_node = get_set_nodee(data, "OLDPWD", "");
	if (oldpwd_node)
	{
		free(oldpwd_node->value);
		oldpwd_node->value = ft_strdup(data->oldpwd);
	}
	pwd_node = get_set_nodee(data, "PWD", "");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(cwd);
	}
	update_env_array(data);
	free(data->oldpwd);
	data->oldpwd = cwd;
}
