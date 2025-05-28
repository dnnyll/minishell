/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:22 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 14:27:45 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

char	update_quote_state(char c, char quote_state)
{
	if ((c == '\'' || c == '"') && quote_state == '\0')
		return (c);				// opening quote
	if (c == quote_state)
		return ('\0');			// closing quote
	return (quote_state);			// no change
}

t_token	*lexer(const char *input)
{
	// printf("lexer\n");
	t_token	*list;
	int		i;
	char	quote_state;

	list = NULL;
	i = 0;
	quote_state = '\0';
	while (input[i])
	{
		if (quote_state == '\0')
		{
			if (ft_isspace(input[i]))
			{
				i++;
				continue ;
			}
			// Only allow quote parsing if it's at the start of a token
			if ((input[i] == '\'' || input[i] == '"') &&
				(i == 0 || ft_isspace(input[i - 1]) ||
				get_operator_type(&input[i - 1]) != TOKEN_ERROR))
			{
				t_token_result result = extract_quoted(input, i);
				if (result.new_index == -1) // Unterminated quote
				{
					// fprintf(stderr, "minishell: syntax error: unterminated quote\n");
					free_token_list(list);
					return (NULL);
				}
				if (result.token)
					add_token(&list, result.token);
				i = result.new_index;
				continue ;
			}
			if (get_operator_type(&input[i]) != TOKEN_ERROR)
			{
				t_token_result result = extract_operator(input, i);
				if (result.token)
					add_token(&list, result.token);
				i = result.new_index;
				continue ;
			}
			t_token_result result = extract_word(input, i);
			if (result.token)
				add_token(&list, result.token);
			i = result.new_index;
		}
		else
		{
			quote_state = update_quote_state(input[i], quote_state);
			i++;
		}
	}
	return (list);
}
