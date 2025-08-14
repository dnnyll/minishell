#include "minishell.h"

void	free_on_exit(t_data *data)
{
		printf("free_on_exit\n");
		free_tokens(data);						//	frees token list
		free_commands(data);					//	frees command list
		// free(input_line);						//	frees input line add input line to data structure????
}

// free(input_line);
