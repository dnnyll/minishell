/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:22 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/27 07:57:15 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
raw input_line (e.g. echo "hello" > out.txt)
    ↓
[1] Skip whitespace
[2] Detect quotes and extract grouped words
[3] Detect operators (|, <, >, <<, >>)
[4] Extract normal words (echo, out.txt, etc.)
[5] Create a token (value + type)
[6] Add token to linked list
[7] Return linked list
*/

#include "minishell.h"

int	ft_isspace(int c)
{
	if ((c >= 7 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

void	add_token(t_token **list, t_token *new_token)
{
	t_token	*current;

/*
┌────────────┐          ┌───────────────────────────┐
│ t_token    │          │ t_token                   │
│ *current   ├───────>  │ value: "echo"             │
│            │          │ type: WORD                │
│            │          │ next: pointer to next...  │
└────────────┘          └───────────────────────────┘
*/
	if (!list || !new_token)
		return;

	if (*list == NULL)
	{
		*list = new_token;
		return;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_token_list(t_token *token)
{
	t_token	*next;

	while (token)
	{
		next = token->next;
		free(token->value);
		free(token);
		token = next;
	}
}

t_token	*lexer(const char *input)
{
	t_token	*list = NULL;
	int		i = 0;

	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue;
		}

		// Only allow quote parsing if it's at the start of a token
		if ((i == 0 || ft_isspace(input[i - 1]) || \
			get_operator_type(&input[i - 1]) != TOKEN_ERROR)
			&& (input[i] == '\'' || input[i] == '"'))
		{
			t_token_result res = extract_quoted(input, i);
			if (res.new_index == -1) // Unterminated quote
			{
				free_token_list(list);
				return (NULL);
			}
			if (res.token)
				add_token(&list, res.token);
			i = res.new_index;
			continue;
		}
		if (get_operator_type(&input[i]) != TOKEN_ERROR)
		{
			t_token_result res = extract_operator(input, i);
			if (res.token)
				add_token(&list, res.token);
			i = res.new_index;
			continue;
		}
		t_token_result res = extract_word(input, i);
		if (res.token)
			add_token(&list, res.token);
		i = res.new_index;
	}
	return (list);
}
