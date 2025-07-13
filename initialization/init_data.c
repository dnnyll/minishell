#include "minishell.h"

t_data	init_data(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.token_head = NULL;
	data.command_head = NULL;
	data.variables_head = NULL;
	data.last_exit_code_status = 0;
	data.env = NULL;
	data.pipe_count = 0;
	data.command_count = 0;

	return (data);
}
