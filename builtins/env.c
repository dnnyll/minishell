#include "minishell"

int env_builtin(t_data *data)
{
	t_env *current;

	current = data->env_head;
	while (current)
	{
		if (current->value) // only print KEY=VALUE
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
