#include "minishell.h"

void	free_data_list(t_data *data)
{
	if (!data)
		return;

	free_tokens(data);
	free_commands(data);
	free_env_list(data->env_head);
	free_heredoc_list(data->heredoc_head);
	free_char_array(data->environment_var);
	free(data);
}

