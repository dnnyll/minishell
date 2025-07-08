#include "minishell.h"

t_data	*init_data(void)	//declare in minishell.h
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->token_head = NULL;
	data->command_head = NULL;
	data->variables_head = NULL;
	data->env = NULL;
	data->environment_variables = NULL;
	data->last_exit_code_status = 0;
	data->pipe_count = 0;
	data->command_count = 0;
	return (data);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	return(env);
}

// void	launch_init(void)
// {
// 	init_data();
// 	init_
// }