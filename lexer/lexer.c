/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:19:22 by daniefe2          #+#    #+#             */
/*   Updated: 2025/05/22 16:49:55 by daniefe2         ###   ########.fr       */
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


// ──────────────────────────────────────────────
// LEXER WORKFLOW: FROM raw input TO token list
// ──────────────────────────────────────────────

INPUT: a raw input string, like:
    echo "hello world" | grep hi > file.txt

GOAL: break it into a linked list of tokens like:
    [WORD:echo] → [WORD:hello world] → [PIPE:|] → [WORD:grep] → [WORD:hi] → [REDIR_OUT:>] → [WORD:file.txt]

// ──────────────────────────────────────────────
// [1] Skip Whitespace
//    - Skip spaces or tabs between tokens.
// ──────────────────────────────────────────────
    while (isspace(line[i]))
        i++;

// ──────────────────────────────────────────────
// [2] Handle Quoted Strings
//    - If you find a quote (' or "), capture everything inside.
//    - Support escaping (optional now, later you may need it).
// ──────────────────────────────────────────────
    if (line[i] == '\'' || line[i] == '"')
        extract until matching quote → store as WORD

// ──────────────────────────────────────────────
// [3] Detect Operators
//    - Recognize token types like:
//        |, <, >, >>, <<
// ──────────────────────────────────────────────
    if (line[i] == '|')
        type = T_PIPE;
    else if (line[i] == '<')
        if (line[i + 1] == '<') → T_HEREDOC
        else → T_REDIR_IN;
    else if (line[i] == '>')
        if (line[i + 1] == '>') → T_REDIR_APPEND
        else → T_REDIR_OUT

    advance `i` accordingly (1 or 2 chars)

// ──────────────────────────────────────────────
// [4] Extract Unquoted Words
//    - Any sequence of non-whitespace, non-operator, non-quote
// ──────────────────────────────────────────────
    start = i;
    while (line[i] is not space, not operator, not quote)
        i++;
    str = substr(line, start, i - start)
    type = T_WORD

// ──────────────────────────────────────────────
// [5] Create Token
// ──────────────────────────────────────────────
    token = token_new(str, type);
    add to linked list

// ──────────────────────────────────────────────
// [6] Return Head of Linked List
// ──────────────────────────────────────────────
    return list;

*/

#include "minishell.h"

t_token	*lexer(char *input_line)
{
	while (input_line != '\0')
	{
		while (input_line[i] == ' ' || (input_line[i] => 7 && input_line[i] <= 13));
		{
			i++;
			if (input_line[i] == '\'' || input_line[i] == '"')
			//	extract and store the word
			if (input_line[i] == '|')
				type = TOKEN_PIPE;
			else if (input_line[i] == '<')
			{
				if (input_line[i + 1] == '<')
					type = TOKEN_HEREDOC;
				else
					type = TOKEN_REDIR_IN;
			}
			else if (input_line[i] == '>')
			{
				if (input_line[i + 1] == '<')
					type = TOKEN_REDIR_APPEND;
				else
					type = TOKEN_REDIR_OUT;
			}
		}
	}
}
