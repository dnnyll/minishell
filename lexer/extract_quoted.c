/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_quoted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:57:58 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/28 10:24:13 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quoted_length(const char *input, char quote_char)
{
	int	len;
	
	len= 0;
	while (input[len])
	{
		if (input[len] == quote_char)
			return (len);
		len++;
	}
	return (-1); // Closing quote not found
}

char	*extract_quoted_value(const char *input, int len)
{
	char	*value;

	value = malloc(len + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, input, len + 1);
	return (value);
}

t_token_result	extract_quoted(const char *input, int i)
{
	t_token_result	res;
	t_token			*token;
	char			*token_value;
	char			quote;
	int				len;

	quote = input[i];
	len = get_quoted_length(input + i + 1, quote);
	if (len == -1)
	{
		fprintf(stderr, "minishell: syntax error: unterminated quote\n");
		return ((t_token_result){NULL, -1}); // return -1 to indicate lexer should abort
	}
	token_value = ft_substr(input, i + 1, len);
	if (!token_value)
		return ((t_token_result){NULL, i});
	token = create_token(token_value, TOKEN_WORD);
	free (token_value);
	if (!token)
	{
		free(token);
		return ((t_token_result){NULL, i});
	}
	res.token = token;
	res.new_index = i + len + 2; // skip both opening and closing quotes
	return (res);
}
