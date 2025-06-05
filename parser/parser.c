/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:46:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/05 14:47:04 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_token	*head)
{
	t_token	*temp = head;	//“Give me the address of the first node in your token list, and I’ll walk through the list using the next pointers.”
	
	int	count_nodes = 0;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_WORD)
			count_nodes++;
		else if (temp->type == TOKEN_REDIR_IN || temp->type == TOKEN_REDIR_OUT)
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
void	**argument_fill(char **argv, t_token *head) 
{
	t_token *temp = head;
	int		i = 0;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_WORD)
		{
			argv[i] = ft_strdup(temp->value);	//	we allocate a copy of a string
			i++;
		}
		else if (temp->type == TOKEN_REDIR_IN || temp->type == TOKEN_REDIR_OUT)
		{
			temp = temp->next;
		}
	}
	argv[i] == NULL;
}

// void	argument_collector(t_token result, char **argv)
// {
	// t_token *temp = ?
	// int	size = count_nodes(t_token	result);
// 	alloc_argv(argv, size);
// 	argument_fill(argv, t_token result)
// }