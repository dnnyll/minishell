/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variable_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:08:59 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/18 10:09:53 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variable(t_data *data, char *value)
{
	
}
void	handle_variable(t_data *data, t_token *tokens)
{
	t_token	*current = tokens;
	char *expanded;

	while (current && current->next != NULL) // or current != end
	{
		if (tokens->type == WORD && tokens->type != SINGLE_QUOTE)
		{
			if (ft_strchr(current->value, '$'));
			{
				expanded = expand_variable(data, current->value);
				if(!expanded)
					return (perror("Error: expanding variable @ handle_variable"));
				free (current->value); //really?
				current->value = expanded;
			}
		}
		current = current->next;
	}
}

