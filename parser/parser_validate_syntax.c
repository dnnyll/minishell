/*
to do:
	stil needs to get the errors printed correctly in the error output, check
	pipe function for it already contains a correct print version commented
	for every case.
*/

#include "minishell.h"

/*
	information concerning: get_last_token

	purpose: returns the last token in a linked list of tokens.

	for: any command like echo hello | grep h

	it walks through the list of tokens until it reaches the one 
	that has no next token, then returns it.

	this is often used to check the position of the last token 
	for syntax validation (e.g., pipe at the end).
*/
t_token	*get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

/*
	information concerning: verify_pipes

	purpose: checks for invalid pipe usage in the token list.

	for: echo | | ls or | echo

	it verifies:
	- the first token is not a pipe
	- pipes are not repeated (e.g., ||)
	- the last token is not a pipe

	this ensures the command pipeline is well-formed before 
	splitting or executing commands.
*/
int	verify_pipes(t_token *tokens)
{
	t_token	*current = tokens;

	if (!current)
		return (1);
	// 1. Check first token
	if (current->type == PIPE)
		return (print_error("syntax error near unexpected token `|'\n", NULL, NULL), 1);
	while (current && current->next)
	{
		// 2. Check for double pipes (e.g., | |)
		if (current->type == PIPE && current->next->type == PIPE)
			return (print_error("minishell :syntax error near unexpected token `|'\n", NULL, NULL), 1);
		// 2. Check if next is a redirection token after pipe (invalid)
		if (current->type == PIPE &&
			(current->next->type == REDIR_IN || current->next->type == REDIR_OUT
			|| current->next->type == HEREDOC || current->next->type == APPEND))
			return (print_error("minishell: syntax error near unexpected token `newline'\n", NULL, NULL), 1);
		current = current->next;
	}
	// 3. After the loop, current is the last token
	if (current->type == PIPE)
		return (print_error("minishell: syntax error near unexpected token `|'\n", NULL, NULL), 1);
	return (0);
}

/*
	information concerning: verify_redirections

	purpose: checks if redirection operators have valid targets.

	for: echo > or cat < file.txt

	it verifies:
	- every redirection is followed by a WORD token (e.g., filename)
	- no redirection is at the end of the input
	- no redirection is followed by another redirection or invalid token

	this prevents syntax errors related to incomplete or malformed 
	redirections in the command.
*/
int	verify_redirections(t_token *tokens)
{
	t_token		*current = tokens;
	const char	*unexpected;

	if (!current)
		return (1);
	while (current)
	{
		if (is_redirection(current->type))
		{
			// Case 1: redirection is the last token (no target)
			if (!current->next)
				return (print_error("syntax error near unexpected token `newline'\n", NULL, NULL), 1);
			// Case 2: redirection is followed by something that's not a WORD
			if (current->next->type != WORD)
			{
				unexpected = current->next->value;
				return (print_error("syntax error near unexpected token `newline'\n", NULL, NULL), 1);	//?????????????
				printf("minishell: syntax error near unexpected token `%s'\n", unexpected);				//?????????????
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

/*
	information concerning: validate_syntax

	purpose: validates the overall syntax of a tokenized command.

	for: any shell input like echo hello | grep h > out.txt

	it performs:
	- checks for a pipe at the beginning or end of the token list
	- calls verify_pipes() to ensure correct pipe usage (no double or misplaced pipes)
	- calls verify_redirections() to ensure redirection operators are followed by valid targets

	this acts as a central checkpoint to catch syntax errors before
	attempting to execute or expand the command.
*/
int	validate_syntax(t_token *tokens)
{
	//printf("entered validade_syntax\n");
	t_token	*last_token;

	if (!tokens)
		return (printf("Error: no tokens @ validate_syntax\n"), 1);
	last_token = get_last_token(tokens);

	// Check if the first or last token is a pipe
	if (tokens->type == PIPE || last_token->type == PIPE)
		return (print_error("minishell: syntax error near unexpected token `|'\n", NULL, NULL), 1);
	// Run pipe checks
	if (verify_pipes(tokens) == 1)
		return (1);
	// Run redirection checks
	if (verify_redirections(tokens) == 1)
		return (1);
	return (0);
}
