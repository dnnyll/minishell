#include "minishell.h"

/*
	information concerning: expand_token_values

	purpose: expands variables (e.g. $HOME, $USER) inside tokens that
	are marked as expandable.

	for: echo "Hello $USER"

	it processes:
	- every token marked as `expandable`
	- replaces its `value` with the result of `process_variables`,
	which evaluates environment variables

	this ensures that commands reflect the actual runtime values
	from the environment 
	before being executed (like turning `echo $HOME` into `echo /home/user`).
*/
void	expand_token_values(t_token *tokens, t_data *data)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	if (!tokens)
		return ;
	while (current)
	{
		if (current->expandable)
		{
			printf("Expanding: value='%s'\n", current->value);
			expanded = process_variables(current->value, data, current);
			free (current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}
