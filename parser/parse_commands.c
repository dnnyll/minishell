/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/09 14:54:12 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int count_nodes(t_token *head)
// {
// 	int count = 0;
// 	t_token *temp = head;	//“Give me the address of the first node in your token list, and I’ll walk through the list using the next pointers.”

// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == WORD)
// 			count++;
// 		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
// 			|| temp->type == APPEND || temp->type == HEREDOC)
// 			temp = temp->next; // skip redirection target
// 		temp = temp->next;
// 	}
// 	return (count);
// }


// char **argument_collect(t_token *head)
// {
// 	int size = count_nodes(head);
// 	char **argv = malloc(sizeof(char *) * (size + 1));
// 	if (!argv)
// 		return (NULL);
// 	return argument_fill(argv, head);
// }

// char **argument_fill(char **argv, t_token *head)
// {
// 	t_token *temp = head;
// 	int i = 0;

// 	while (temp && temp->type != PIPE)
// 	{
// 		if (temp->type == WORD)
// 		{
// 			argv[i++] = ft_strdup(temp->value);
// 			temp = temp->next;
// 		}
// 		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
// 			|| temp->type == APPEND || temp->type == HEREDOC)
// 		{
// 			temp = temp->next; // skip file token
// 			if (temp)
// 				temp = temp->next;
// 		}
// 		else
// 			temp = temp->next;
// 	}
// 	argv[i] = NULL;
// 	return argv;
// }


// char **argument_collect(t_token *head)
// {
// 	char	**argv;
// 	int	size = count_nodes(head);
// 	argv = alloc_argv(NULL, size);
// 	if (!argv)
// 		return (NULL);
// 	argument_fill(argv, head);
// 	return (argv);
// }

void	fill_command_segment(t_command *command, t_token *start, t_token *end)
{
	// Walk from start to end (not including end)
	// Fill command->argv, infile, outfile, etc.
	// This comes next!
}

t_command	*new_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->heredoc_delim = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->append = 0;
	command->is_builtin = 0;
	command->next = NULL;
	return (command);
}

void	add_command_back(t_command **head, t_command *new_command)
{
	if (!*head)
	{
		*head = new_command;
		return ;
	}
	t_command *temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_command;
}


void	parse_commands(t_data *data, t_token *tokens)
{
	t_token	*current = tokens;
	t_token	*segment_start = current;

	while (current)
	{
		if (current->type == PIPE)
		{
			// Cut the segment here
			current->type = T_EOF;  // Optional: mark the pipe visually

			// Parse the segment [segment_start ... current (exclusive)]
			t_command *command = new_command();
			if (!command)
				return ; // handle error
			fill_command_segment(command, segment_start, current); // You'll write this
			add_command_back(&data->command_head, command);

			segment_start = current->next; // move to next segment
		}
		current = current->next;
	}
	// Handle the final segment (after last pipe or if no pipes)
	if (segment_start)
	{
		t_command *command = new_command();
		if (!command)
			return ; // handle error
		fill_command_segment(command, segment_start, NULL); // NULL = until end
		add_command_back(&data->command_head, command);
	}
}

