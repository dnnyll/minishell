/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variable_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:31:46 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:31:47 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_exit_code(t_data *data, char *input)
{
	char	*status;
	char	*result;

	status = ft_itoa(data->last_exit_code_status);
	result = ft_strjoin(input, status);
	free (status);
	return (result);
}

char	*dollar_case(const char *input, int *i, char *result, t_data *data)
{
	char	*temp;

	(*i)++;
	if (input[*i] == '?')
	{
		temp = handle_exit_code(data, result);
		free(result);
		result = temp;
		(*i)++;
	}
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
	{
		temp = handle_environment_variables(input, i, data, result);
		free(result);
		result = temp;
	}
	else
	{
		temp = ft_strjoin_char(result, '$');
		free(result);
		result = temp;
	}
	return (result);
}

char	*expand_variables(const char *input, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = strdup("");
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
			result = dollar_case(input, &i, result, data);
		else
			result = append_char_to_result(result, input[i], &i);
	}
	return (result);
}

//	extra note: this is a flaggin 0 or 1 either if they are or arent expandable
void	handle_variables(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == WORD && current->quote != SINGLE_QUOTE
			&& is_expandable_variable(current->value))
			current->expandable = 1;
		else
			current->expandable = 0;
		current = current->next;
	}
}

char	*process_variables(const char *input, t_data *data, t_token *tokens)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	handle_variables(current);
	expanded = expand_variables(input, data);
	return (expanded);
}
