/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:33:01 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:33:11 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			expanded = process_variables(current->value, data, current);
			free (current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}
