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


*/





#include "minishell.h"

t_token *get_last_token(t_token *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

// we have got a problem with pipe verification and also we havent set a previous type in our structure, need to look into it
int	verify_pipes(t_token *tokens)
{
	printf("verify_pipes\n");
	t_token	*current = tokens;

	if (!current)
		return (1); // empty input is technically valid
	// 1. Check first token
	if (current->type == PIPE)
		return (printf("ERROR: pipe at beginning\n"), 1);
	while (current && current->next)
	{
		// 2. Check for double pipes (e.g., | |)
		if (current->type == PIPE && current->next->type == PIPE)
			return (printf("ERROR: two pipes in a row\n"), 1);
		current = current->next;
	}
	// 3. After the loop, current is the last token
	if (current->type == PIPE)
		return (printf("ERROR: pipe at the end\n"), 1);
	return (0); // Success: pipe usage is valid
}


int	verify_redirections(t_token *tokens)
{
	t_token		*current = tokens;
	const char	*unexpected;

	unexpected = NULL;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!current->next || current->next->type != WORD)
			{
				if (current->next)
					unexpected = current->next->value;
				else
					unexpected = "new line\n";
				return (printf("minishell: syntax error near unexpected token `%s'\n", unexpected), 0);
			}
			if (is_redirection(current->next->type))
				return (printf("minishell: syntax error near unexpected token `%s'\n", unexpected), 0);
		}
		current = current->next;
	}
	return (1);
}


int	validate_syntax(t_token *tokens)
{
	t_token	*last_token;

	if (!tokens)
		return (printf("Error: no tokens @ validate_syntax\n"), 0);
	last_token = get_last_token(tokens);
	// Check if the first or last token is a pipe
	if (tokens->type == PIPE || last_token->type == PIPE)
		return (printf("Error: syntax error '|' @ validate_syntax\n"), 0);
	if (!verify_pipes(tokens))
		return (0);
	if (!verify_redirections(tokens))
		return (0);
	return (1);
}


