#include "minishell.h"

// void	free_data_list(t_data *data)
// {
// 	printf("print free_data_list\n");
// 	if (!data)
// 		return;

// 	free_tokens(data);
// 	free_commands(data);
// 	free_env_list(data->env_head);
// 	free_heredocs_in_command(data->command_head);
// 	free_char_array(data->environment_var);
// 	free(data);
// }

void free_data_list(t_data **data_ptr)
{
	t_data *data;

	if (!data_ptr || !*data_ptr)
		return ;
	data = *data_ptr;
	printf("print free_data_list\n");
	free_tokens(data);
	free_commands(data);
	free_env_list(data->env_head);
	// free_heredocs_in_command(data->command_head);
	free_char_array(data->environment_var);
	free(data);
	*data_ptr = NULL;
}

