/* **************************************************************************** */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                           DEAD INSIDE                                        */
/*                                                                              */
/*                                                                              */
/*                                       MROSSET & DANIEFE2                     */
/*                                                                              */
/*                                                                              */
/* **************************************************************************** */

#include "minishell.h"

char	*search_list_env_value(t_env *env_head, const char *name)
	{
	t_env *current = env_head;
	while (current)
	{
		if (strcmp(current->key, name) == 0)
		{
			printf("DEBUG: found match! value = [%s]\n", current->value);
			return current->value;
		}
		current = current->next;
	}
	return (NULL);
}

void	add_env_node(t_env **head, t_env *new_node)
{
	if (!head || !new_node)
	return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	t_env	*current = *head;
	while (current->next)
	current = current->next;
	current->next = new_node;
}

void	free_env_list(t_env *env)
{
	t_env	*next;
	
	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}

t_env	*create_node(const char *env_var_line)
{
	int	equal_pos;
	t_env *env = malloc(sizeof(t_env));

	if (!env)
		return (NULL);
	equal_pos = 0;
	while (env_var_line[equal_pos] && env_var_line[equal_pos] != '=')
		equal_pos++;
	if(env_var_line[equal_pos] != '=')
	{
		env->key = ft_strdup(env_var_line);
		env->value = ft_strdup("");
	}
	else
	{
		env->key = ft_substr(env_var_line, 0, equal_pos);
		env->value = ft_substr(env_var_line, equal_pos + 1, ft_strlen(env_var_line));
	}
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return NULL;
	}
	env->next = NULL;
	return (env);
}

t_env *build_env_list(char **environment_var)
{
	t_env *head = NULL;
	int i = 0;
	t_env *node;

	while (environment_var[i])
	{
		node = create_node(environment_var[i]);
		if (!node)
		{
			free_env_list(head);  // Clean up on failure
			return NULL;
		}
		add_env_node(&head, node);
		i++;
	}
	return head;
}

