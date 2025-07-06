#include "minishell.h"

//	allows the command struct to be free to make sure the commands dont stack
//	with every call that is made in the terminal.
void	free_commands(t_data *data)
{
	t_command *current = data->command_head;
	t_command *next;
	while (current)
	{
		next = current->next;
		// Free argv array
		if (current->argv)
		{
			int i = 0;
			while (current->argv[i])
			{
				free(current->argv[i]);
				i++;
			}
			free(current->argv);
		}
		// Free redirection files and heredoc delimiter
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		// No need to close fd_in / fd_out here unless you're manually opening files elsewhere
		free(current);
		current = next;
	}
	data->command_head = NULL;
}

int	count_arguments(t_token *start, t_token *end)
{
	// printf("count_arguments\n");
	t_token *current = start;
	int	count_arguments;

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
	// printf("allocate_command_argv\n");
	char **argv;

	argv = malloc(sizeof(char*) * (argc + 1));
	if (!argv)
	{
		printf("Error allocating memory for command->argv at fill_command_segment\n");
		return (NULL);
	}
	argv[argc] = '\0';
	return (argv);
}

void	fill_argv(t_command *command, t_token *start, t_token *end)
{
	// printf("fill_argv\n");
	t_token *current = start;
	int	i;

	i = 0;
	while (current && current != end)
	{
		if (current->type == WORD)
		{
			command->argv[i] = ft_strdup(current->value);
			i++;
		}
		else if (is_redirection(current->type))
			current = current->next; // skip the filename
		current = current->next;
	}
}

void	fill_command_segment(t_command *command, t_token *start, t_token *end)
{
	// printf("fill_command_segment\n");
	int	argc;
	
	argc = count_arguments(start, end);
	command->argv = allocate_command_argv(argc);
	if (!command->argv)
		return(perror("Error: malloc command->argv @ fill_command_segment"));	// needs handle malloc failure
	fill_argv(command, start, end);
	handle_redirections(command, start, end);
}
