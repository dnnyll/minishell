#include "minishell.h"

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_list(void *head, void *(*get_next)(void *),
		void (*free_node)(void *))
{
	void	*next;

	while (head)
	{
		next = get_next(head);
		free_node(head);
		head = next;
	}
}
