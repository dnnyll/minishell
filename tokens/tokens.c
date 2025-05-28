/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:21:51 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 11:06:19 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
┌────────────┐          ┌───────────────────────────┐
│ t_token    │          │ t_token                   │
│ *current   ├───────>  │ value: "echo"             │
│            │          │ type: WORD                │
│            │          │ next: pointer to next...  │
└────────────┘          └───────────────────────────┘
*/

void	add_token(t_token **list, t_token *new_token)
{
	// printf("add_token\n");
	t_token	*current;

	if (!list || !new_token)
		return ;
	if (*list == NULL)
	{
		*list = new_token;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_token_list(t_token *token)
{
	// printf("free_token_list\n");
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

t_token	*create_token(const char *value, t_token_type type)
{
	// printf("create_token\n");
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return(NULL);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}