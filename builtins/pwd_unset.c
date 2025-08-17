/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marjorie <marjorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 22:47:03 by marjorie          #+#    #+#             */
/*   Updated: 2025/08/17 23:29:36 by marjorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **args)
{
	char	*cwd;

	(void)args;
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

void	unset_env_node(t_data *data, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = data->env_head;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& current->key[ft_strlen(key)] == '\0')
		{
			if (prev)
				prev->next = current->next;
			else
				data->env_head = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	unset_builtin(char **args, t_data *data)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			print_error("minishell: unset: `", args[i], "': not a valid"
				" identifier\n");
			data->last_exit_code_status = 1;
		}
		else
			unset_env_node(data, args[i]);
		i++;
	}
	if (data->environment_var)
		free_char_array(data->environment_var);
	data->environment_var = env_list_to_array(data->env_head);
	return (0);
}

/*
**pwd_builtin: displays the absolute path of the current directory, follow by
	a new line. This funtion work for the command "pwd" only.
**cwd: current working directory
**getcwd: If we pass NULL as the first arg and 0 as the 2nd, it automatically
	allocates memory to store the current directory path.
**should_remove: Calculate the length of var_name, compare this portion with the
	beginning of entry. Checks that the following char is an '=' (to avoid
	deleting variable with the same prefix).
**remove_env_entry: This function is for remove a specific env variable from the
	env. It counts the number of entries in env, allocates a new array. Copies
	the variable except the one to be removed, using should_remove and frees the
	old array.
**unset_builtin: This is the main unset builtin function. It iterates through the
	argsgiven after unset. For each valid name(using is_valid_identifier) calls
	remove_env_entry. Displays an error message if the identifier is invalid.
	Returns 0 in all cases (as expected by the unset builtin in bash).
*/