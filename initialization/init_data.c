#include "minishell.h"

t_data	init_data(void)	//declare in minishell.h
{
	t_data	data;
	data.token_head = NULL;
	data.command_head = NULL;
	data.variables_head = NULL;

	// keep on adding whatever you need to initiatlize;

	return (data);
}