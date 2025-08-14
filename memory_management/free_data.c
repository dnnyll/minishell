#include "minishell.h"

void	free_data_list(t_data **data_ptr)
{
	t_data	*data;

	if (!data_ptr || !*data_ptr)
		return ;
	data = *data_ptr;
	free_tokens(data);
	free_commands(data);
	free_env_list(data->env_head);
	free_char_array(data->environment_var);
	free(data);
	*data_ptr = NULL;
}
