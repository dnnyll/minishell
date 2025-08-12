#include "minishell.h"

int	count_arguments(t_token *start, t_token *end)
{
	t_token	*current;
	int		count_arguments;

	current = start;
	count_arguments = 0;
	while (current && current != end)
	{
		if (current->type == WORD)
			count_arguments++;
		else if (is_redirection(current->type))
			current = current->next;
		current = current->next;
	}
	return (count_arguments);
}

char	**allocate_command_argv(int argc)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		printf("Error allocating memory for command->argv at"
			"fill_command_segment\n");
		return (NULL);
	}
	argv[argc] = '\0';
	return (argv);
}

void	fill_argv(t_command *command, t_token *start, t_token *end)
{
	t_token	*current;
	int		i;

	current = start;
	i = 0;
	while (current && current != end)
	{
		if (current->type == WORD)
		{
			command->argv[i] = ft_strdup(current->value);
			i++;
		}
		else if (is_redirection(current->type))
			current = current->next;
		current = current->next;
	}
}

void	fill_command_segment(t_command *command, t_token *start, t_token *end)
{
	int	argc;

	argc = count_arguments(start, end);
	command->argv = allocate_command_argv(argc);
	if (!command->argv)
		return (perror("Error: malloc command->argv @ fill_command_segment"));
	fill_argv(command, start, end);
	handle_redirections(command, start, end);
}
