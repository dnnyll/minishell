#include "minishell.h"

void	free_on_exit(t_data *data)
{
	free_tokens(data);
	free_commands(data);
}

// free(input_line);
