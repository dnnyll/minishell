#include "minishell.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return;
	free(node->key);
	free(node->value);
	free(node);
}
void	free_env_list(t_env *env)
{
	printf("free_env_node\n");
	t_env	*next;
	
	while (env)
	{
		next = env->next;
		free_env_node(env);
		env = next;
	}
}