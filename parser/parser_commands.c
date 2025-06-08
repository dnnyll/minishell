/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/06 13:41:06 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_token	*head)
{
	t_token	*temp = head;	//“Give me the address of the first node in your token list, and I’ll walk through the list using the next pointers.”
	
	int	count_nodes = 0;
	while (temp && temp->type)
	{
		if (temp->type)
			count_nodes++;
		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
			temp = temp->next;
		temp = temp->next;
	}
	return (count_nodes);
}

char	**alloc_argv(char **argv, int size)
{
	argv = malloc(sizeof(char *) * (size + 1));
	if (!argv)
		return (NULL);
	return (argv);
}

char	**argument_fill(char **argv, t_token *head) 
{
	t_token *temp = head;
	int		i = 0;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == WORD)
		{
			argv[i] = ft_strdup(temp->value);
			i++;
		}
		else if (temp->type == REDIR_IN || temp->type == REDIR_OUT)
			temp = temp->next;
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

char **argument_collect(t_token *head)
{
	char	**argv;
	int	size = count_nodes(head);
	argv = alloc_argv(NULL, size);
	if (!argv)
		return (NULL);
	argument_fill(argv, head);
	return (argv);
}