/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:33:19 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:33:25 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **list, t_token *new_token)
{
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

t_token	*create_token(const char *value, t_token_type type)
{
	t_token	*token;

	token = init_token();
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	return (token);
}
