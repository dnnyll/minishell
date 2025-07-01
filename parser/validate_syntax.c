/*

╔══════════════════════════════════════════════════════════════════════╗
║              PIPE VALIDATION STRATEGY – TEXT DIAGRAM                ║
╠══════════════════════════════════════════════════════════════════════╣
║ Rule 1: If current->type == PIPE                                    ║
║   ┌──────────────────────────────────────────────────────────────┐  ║
 ║  │  Whenever we see a PIPE token, we must check its neighbors:  │  ║
║   └──────────────────────────────────────────────────────────────┘  ║
  ║                                                                    ║
 ║┌──────────────────────────────────────────────────────────────┐   ║
 ║│ Rule 2: If !current->previous or !current->next → INVALID         │   ║
║ └──────────────────────────────────────────────────────────────┘   ║
║    ❌ Example:                                                     ║
║       [ PIPE ][ ls ]              → starts with PIPE             ║
║       [ ls ][ PIPE ]              → ends with PIPE               ║
║       ↑         ↑                                               ║
║       No previous   No next         → INVALID                        ║
║                                                                    ║
║ ┌──────────────────────────────────────────────────────────────┐   ║
║ │ Rule 3: If previous is PIPE or redirection → INVALID              │   ║
║ └──────────────────────────────────────────────────────────────┘   ║
║    ❌ Example:                                                     ║
║       [ ls ][ PIPE ][ PIPE ][ grep ]                            ║
║                    ↑ previous is PIPE → INVALID                     ║
║                                                                ║
║       [ > ][ file.txt ][ PIPE ][ grep ]                         ║
║                             ↑ previous is redirection → INVALID     ║
║                                                                    ║
║ ┌──────────────────────────────────────────────────────────────┐   ║
║ │ Rule 4: If next is PIPE or redirection → INVALID              │   ║
║ └──────────────────────────────────────────────────────────────┘   ║
║    ❌ Example:                                                     ║
║       [ ls ][ PIPE ][ PIPE ][ grep ]                            ║
║                          ↑ next is PIPE → INVALID               ║
║                                                                ║
║       [ ls ][ PIPE ][ > ][ file.txt ]                           ║
║                    ↑ next is redirection → INVALID              ║
║                                                                    ║
║ ✅ VALID EXAMPLES:                                                ║
║   [ ls ][ PIPE ][ grep ]        → VALID                          ║
║   [ cat ][ infile ][ PIPE ][ wc ][ -l ] → VALID                 ║
║                                                                    ║
╚══════════════════════════════════════════════════════════════════════╝




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
t_token *get_last_token(t_token *head)
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
	// printf("verify_pipes\n");
	t_token	*current = tokens;

	if (!current)
		return (1); // empty input is technically valid
	// 1. Check first token
	if (current->type == PIPE)
		return (printf("ERROR: pipe at beginning\n"), 1);
		// fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
	while (current && current->next)
	{
		// 2. Check for double pipes (e.g., | |)
		if (current->type == PIPE && current->next->type == PIPE)
			return (printf("ERROR: two pipes in a row\n"), 1);
			// fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
		// 2. Check if next is a redirection token after pipe (invalid)
		if (current->next->type == REDIR_IN || current->next->type == REDIR_OUT
			|| current->next->type == HEREDOC || current->next->type == APPEND)
			return (printf("ERROR: redirection after pipe\n"), 1);
			// fprintf(stderr, minishell: syntax error near unexpected token `>'\n);
		current = current->next;
	}
	// 3. After the loop, current is the last token
	if (current->type == PIPE)
		return (printf("ERROR: pipe at the end\n"), 1);
		// fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
	return (0); // Success: pipe usage is valid
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
	// printf("verify_redirections\n");
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
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			// Case 2: redirection is followed by something that's not a WORD
			if (current->next->type != WORD)
			{
				unexpected = current->next->value;
				printf("minishell: syntax error near unexpected token `%s'\n", unexpected);
				return (0);
			}
		}
		current = current->next; // move to the next token
	}
	return (1); // Success: redirections are valid
}


int	validate_syntax(t_token *tokens)
{
	t_token	*last_token;

	if (!tokens)
		return (printf("Error: no tokens @ validate_syntax\n"), 1);

	last_token = get_last_token(tokens);

	// Check if the first or last token is a pipe
	if (tokens->type == PIPE || last_token->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}

	// Run pipe checks
	if (verify_pipes(tokens))
		return (1);

	// Run redirection checks
	if (verify_redirections(tokens))
		return (1);

	return (0);
}




