#include "minishell.h"

/*
	information concerning: expand_token_values

	purpose: expands variables (e.g. $HOME, $USER) inside tokens that are marked as expandable.

	for: echo "Hello $USER"

	it processes:
	- every token marked as `expandable`
	- replaces its `value` with the result of `process_variables`, which evaluates environment variables

	this ensures that commands reflect the actual runtime values from the environment 
	before being executed (like turning `echo $HOME` into `echo /home/user`).
*/
void	expand_token_values(t_token *tokens, t_data *data)
{
	t_token	*current = tokens;
	char	*expanded;

	expanded = process_variables(current->value, data, current);
	while (current)
	{
		if (current->expandable)
		{
			expanded = process_variables(current->value, data, current);
			free (current->value);
			current->value = expanded;  // replace with expanded value
		}
		current = current->next;
	}
}