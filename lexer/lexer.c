/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:22 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/29 15:18:10 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || (c == 32))
		return (1);
	return (0);
}
int is_operator_start(const char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	update_quote_state(char c, char quote_state)
{
	if ((c == '\'' || c == '"') && quote_state == '\0')
		return (c);				// opening quote
	if (c == quote_state)
		return ('\0');			// closing quote
	return (quote_state);			// no change
}

t_token_result extract_token(const char *input, int start)
{
	if (input[start] == '\'' || input[start] == '"')
		return extract_quoted(input, start);

	if (is_operator_start(input[start]))
		return extract_operator(input, start);

	return extract_word(input, start);
}

t_token	*lexer(const char *input)
{
	// printf("lexer\n");
	t_token	*list;
	int		i;


	list = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		t_token_result	result = extract_token(input, i);
		if (result.new_index == -1)
		{
			free_token_list(list);
			return (NULL);
		}
		if (result.token)
			add_token(&list, result.token);
		i = result.new_index;
	}
	return (list);
}
