/*

===============================
 Variable Expansion Plan
===============================

GOAL:
Expand environment variables (e.g., $USER, $?, ${PATH}) in WORD tokens
if they are marked as expandable.

CONSTRAINTS:
- Do not expand inside single quotes
- Expand inside double quotes or unquoted
- Input is already tokenized and quoted
- Environment is stored in char **envp

-------------------------------
STAGE 1: Entry Point
-------------------------------

void handle_variable(t_token *tokens, char **envp);

For each token:
  if token->type == WORD && token->expandable == 1:
    - Call expand_variables(token->value, envp)
    - Replace token->value with result

-------------------------------
STAGE 2: Expand Logic
-------------------------------

char *expand_variables(const char *input, char **envp);

Steps:
1. Create an empty result string
2. Iterate over input character by character
3. On `$`, handle one of the following cases:
   - "$?"      → replace with exit code (from global)
   - "$VAR"    → extract VAR name and look it up
   - "${VAR}"  → extract VAR name between braces
   - "$" alone → treat as empty string
   - Invalid name → treat `$` as literal
4. Append any literal characters to result
5. Return new expanded string

-------------------------------
STAGE 3: Extract Variable Name
-------------------------------

char *extract_var_name(const char str[i], int *len);

- If input starts with `{`, extract until `}`
- Else, extract while [A-Za-z0-9_]
- Set *len to number of characters consumed

-------------------------------
STAGE 4: Lookup Variable
-------------------------------

char *get_env_value(const char *name, char **envp);

- Iterate through envp
- Find "NAME=VALUE"
- If match, return VALUE (duplicated)
- If not found, return empty string

Special case:
  if name == "?" → return ft_itoa(global_exit_status)

-------------------------------
STAGE 5: Utilities
-------------------------------

char str[i]_join_and_free(char *s1, const char *s2);
  - Joins s1 + s2, frees s1, returns new string

char *substrdup(const char *src, int start, int len);
  - Duplicates substring from src[start] to src[start+len]

-------------------------------
EXAMPLES
-------------------------------

Input: "Hello $USER"            → "Hello alice"
Input: "$PATH is the path"     → "/usr/bin:/bin is the path"
Input: "$?"                    → "0" (or other exit code)
Input: "${HOME}"               → "/home/alice"
Input: "$"                     → "" (empty string)
Input: "$USER!"                → "alice!"

-------------------------------
NOTES
-------------------------------

- Variable expansion happens after tokenization
- Result replaces token->value
- No variable expansion inside single quotes
- Braced syntax `${VAR}` is optional, but nice to support
- Your get_env_value must not modify envp
*/

#include "minishell.h"

/*

This is an example of how this file is working


Input: "Hello $USER, status: $?"

-------------------------------
Main loop scanning input string
-------------------------------

i = 0 to end of input:
  if input[i] != '$'
    → append input[i] literally to result
    → i++

  else if input[i] == '$'
    → call handle_variable_expansion(input, &i, data, result)
    → update result with returned string
    → i updated inside handle_variable_expansion to position after variable name or special var

-------------------------------
handle_variable_expansion function
-------------------------------

1) Check char after '$': input[i + 1]

2) If alphanumeric or underscore:
    → Extract variable name starting at input[i + 1]
    → (Inside handle_variable_expansion)
    → Advance i while input[i] is valid variable char (alnum or '_')
    → Extract substring var_name = input[start_index..i-1]

3) If special variable '?':
    → Get last exit code from data->last_exit_code
    → Convert exit code to string

4) Lookup environment value of var_name (or special variable string)

5) Append value to result string, freeing old result to avoid leaks

6) Return new result string and updated i (position after variable)

-------------------------------
Back to main loop:
------------------------------- 

Continue scanning input from updated i

---

### Step-by-step trace example with "Hello $USER, status: $?"

| i  | input[i] | Action                                    | Function                   | Result so far            |
|-----|---------|------------------------------------------|----------------------------|-------------------------|
| 0   | 'H'     | Append 'H'                               | main loop append literal   | "H"                     |
| 1   | 'e'     | Append 'e'                               | main loop append literal   | "He"                    |
| 2   | 'l'     | Append 'l'                               | main loop append literal   | "Hel"                   |
| 3   | 'l'     | Append 'l'                               | main loop append literal   | "Hell"                  |
| 4   | 'o'     | Append 'o'                               | main loop append literal   | "Hello"                 |
| 5   | ' '     | Append ' '                               | main loop append literal   | "Hello "                |
| 6   | '$'     | Found '$' → call handle_variable_expansion | main loop calls handle_variable_expansion |                         |
| 7   | 'U'     | Extract var name "USER" (indices 7 to 10) | handle_variable_expansion  |                         |
| 11  | ','     | Lookup env var USER → "alice", append   | handle_variable_expansion returns new result | "Hello alice"            |
| 11  | ','     | Append ','                              | main loop append literal   | "Hello alice,"          |
| 12  | ' '     | Append ' '                              | main loop append literal   | "Hello alice, "         |
| 13-20| chars  | Append literal characters ("status: ")  | main loop append literal   | "Hello alice, status: " |
| 21  | '$'     | Found '$' → call handle_variable_expansion | main loop calls handle_variable_expansion |                         |
| 22  | '?'     | Special var '?' → get last exit code    | handle_variable_expansion  |                         |
| 23  | -       | Append exit code string "0"              | handle_variable_expansion returns new result | "Hello alice, status: 0"|
| 23+ | End     | End of input, null-terminate result      | main loop                  | Final result string      |

---

### Function locations summary

- **Main loop scanning input string:**  
  - Iterates over `input`, appends normal chars directly  
  - Calls `handle_variable_expansion` whenever it finds `$`

- **handle_variable_expansion:**  
  - Extracts variable names or special variables (like `$?`)  
  - Looks up variable values (environment or shell special variables)  
  - Appends expanded value to result string  
  - Updates index pointer to continue scanning after variable

*/

char	*ft_strjoin_char(char *input, char c)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = ft_strlen(input);
	result = malloc(sizeof(char) * len + 2);
	if (!result)
	{
		printf("ft_strloin_char messed up\n");
		free(result);
	}
	while (i < len)
	{
		result[i] = input[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	return (result);
}

char	*handle_exit_code(t_data *data, char *input)
{
	char	*status;
	char	*result;

	status = ft_itoa(data->last_exit_code_status);
	result = ft_strjoin(input, status);
	free (status);
	return (result);
}

char	*handle_environment_variables(const char *input, int *i, t_data *data, char * result)
{
	int		start;
	char	*variable_name;
	char	*value;
	char	*new_result;
	start = *i;

	while (ft_isalnum(input[*i]) || input[*i] == '_')
		(*i)++;	//note: dereference i → get the value it points to
				//		increment that value
				//		So *i gets the value, and then ++ increments it.
	variable_name = ft_substr(input, start, *i - start);
	value = search_env_value(data, variable_name);
	if(!value)
		return (printf("Error: search_env_value not found for the input\n"), NULL);
	free(variable_name);
	new_result = ft_strjoin(result, value);
	return (new_result);
}

char	*expand_variables(const char *input, t_data *data)
{
	int	i;
	char	*result;
	char	*temp;

	i = 0;
	result = strdup("");
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				temp = handle_exit_code(data, result);
				free(result);
				result = temp;
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == '_')
			{
				temp = handle_environment_variables(input, &i, data, result);
				free (result);
				result = temp;
			}
			else
			{
				temp = ft_strjoin_char(result, '$');	//need to code the ft_strjoin_char
				free (result);
				result = temp;
			}
		}
		else
		{
			temp = ft_strjoin_char(result, input[i]);
			// free (result);
			result = temp;
			free(temp);
			i++;
		}
	}
	return(result);
}

int	isexpandable_variable(const char *str)
{
	printf("isexpandable_variable @parser_variable_handling.c\n");
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '\0')
				return (printf("Error: $ followed by nothing\n"), 1); // $ at end, no variable
			if (str[i] == '$' || str[i] == '?' || ft_isalpha(str[i]) || str[i] == '_')
				return (1); // Valid variable name or special
		}
		else
			i++;
	}
	return (0);
}

/*
	information concerning: handle_variable

	purpose: scans the token list and marks tokens that require variable expansion.

	for: commands containing environment variables, e.g. echo "$HOME" $USER

	it detects the presence of the dollar sign '$' outside of single quotes to flag tokens 
	for later expansion of environment variables like $VAR, $? (last exit status), etc.

	- tokens inside single quotes are excluded (no expansion).
	- tokens inside double quotes or unquoted tokens with '$' are flagged.
	- invalid variable names or isolated '$' may be handled later.

	this step is crucial to ensure that variable expansion is applied only where valid,
	after tokenization and quote processing, but before building the argument array.

	without this, the shell would not replace variables with their values before execution.
*/

//	extra note: this is a flaggin 0 or 1 either if they are or arent expandable
void	handle_variables(t_token *tokens)
{
	printf("handle_variables\n");
	t_token	*current = tokens;
	while (current)
	{
		if (current->type == WORD && current->quote != SINGLE_QUOTE && isexpandable_variable(current->value))
			current->expandable = 1;
		else
			current->expandable = 0;
		printf("Value: %-20s | Type: %-10s | Quote: %-7s | Expandable: %s\n",
			current->value,
			token_type_str(current->type),
			quote_type_str(current->quote),
			current->expandable ? "Yes" : "No");
		current = current->next;
	}
}

char	*process_variables(const char *input, t_data *data, t_token *tokens)
{
	t_token *current = tokens;
	char *expanded;

	//	Marks which tokens are expandable
	printf("handle_variables @ process_variables\n");
	handle_variables(current);
	//	Expands variables in the input string using tokens and data
	printf("expand_variables @ process_variables\n");
	expanded = expand_variables(input, data);
	return (expanded);
}

