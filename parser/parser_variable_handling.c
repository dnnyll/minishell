// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser_variable_handling.c                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/18 09:08:59 by daniefe2          #+#    #+#             */
// /*   Updated: 2025/06/19 11:01:36 by daniefe2         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"


// /*
// List of functions to implement for variable expansion:



// 2. int is_valid_var_start(char c);
//    - Returns 1 if 'c' is a valid first character for a variable name (letter or '_'),
//      otherwise returns 0.

// 3. char *extract_var_name(const char *input, int *index);
//    - Starting at input[*index], extracts the variable name (consisting of letters,
//      digits, and underscores) and advances *index to the character after the name.
//    - Returns a newly allocated string containing the variable name.









// Each function should focus on its specific job to keep your code modular,
// easy to maintain, and test.
// */




// /*
// 2. int is_valid_var_start(char c);
//    - Returns 1 if 'c' is a valid first character for a variable name (letter or '_'),
//      otherwise returns 0.
// */
// int is_valid_var_start(char c);
// // return (ft_isalpha(c) || c == '_');



// /*
// 3. char *extract_var_name(const char *input, int *index);
//    - Starting at input[*index], extracts the variable name (consisting of letters,
//      digits, and underscores) and advances *index to the character after the name.
//    - Returns a newly allocated string containing the variable name.
// */

// char	*extract_var_name(char *variable, int i)
// {
// 	int	i;
	
// 	i = 0;
// 	while (variable[i] && (ft_isalnum(variable[i] || variable[i] == '_')))
// 		i++;
// 	return (ft_substr(variable, 0 , i));
	
// }




// /*
// 4. char *get_variable_value(t_data *data, const char *name);
//    - Looks up the value of the variable 'name' in your internal export list or the
//      environment variables.
//    - Returns a newly allocated string with the variable's value or an empty string
//      if not found.
// */
// char *get_variable_value(t_data *data, const char *name);




// /*
// 5. char *handle_nonstandard_var(t_data *data, const char *input, int *index);
//    - Handles special variables like "$?" (exit status).
//    - Advances *index appropriately.
//    - Returns a newly allocated string containing the special variable's value.
// */
// char *handle_nonstandard_var(t_data *data, const char *input, int i)
// {
// 	if(input[i] == '?')
// 	{
// 		i++;
// 		return (ft_ito(data->exit_status));
// 	}
// 	else
// 	{
		
// 	}
	
// }




// /*
// 6. char *append_and_free(char *value, char *addition);
//    - Concatenates 'value' and 'addition' into a new string.
//    - Frees 'value' and 'addition'.
//    - Returns the new concatenated string.
// */
// char *append_and_free(char *result, char *new_part);




// /*
// 7. char *append_char(char *value, char c);
//    - Appends a single character 'c' to 'value'.
//    - Frees the old 'value' and returns the new string.
// */
// char *append_char(char *value, char c);












// /*
//     get_variable_value: Helper to get the value of a single variable.

//     - Takes the variable name (e.g. "PATH", "?", "HOME").
//     - Checks for special variables:
//       - "?" returns exit status from data->exit_status.
//       - Others check environment variables or internal export list.
//     - Returns the variable's value as a string or empty string if not found.
// */
// char *get_variable_value(t_data *data, const char *var_name)
// {
//     // Handle special variables first.
//     // Query environment or internal export for other variables.
//     // Return newly allocated string or "" if none.
// }


// /*
// 	information concerning: expand_variable

// 	purpose: parses a string and replaces any `$VARIABLE` occurrences with
// 	their corresponding values from the environment or shell internals.

// 	for: echo $HOME
// 	- if input = "$HOME/Desktop", output becomes "/Users/foo/Desktop" (example)

// 	steps taken in this function:

// 	1. initialize `value` as an empty string (to store the final expanded result)
// 	2. loop through each character of the input string
// 	3. when encountering a `$` sign:
// 		- if followed by `?`, it expands to the last command's exit status.
// 		- if followed by a valid variable name, extract it and find its value.
// 		- if followed by invalid characters (like `$!`), expand to an empty string.
// 	4. for non-`$` characters, simply copy them into the result string.
// 	5. after each expansion, append the resolved value to the `value` string.

// 	helper functions expected:
// 	- is_valid_var_start(char c): returns if character can start a variable name.
// 	- extract_var_name(input, &i): returns malloc'd variable name and updates index.
// 	- get_variable_value(data, var_name): returns the variable's value from env or export.
// 	- handle_nonstandard_var(data, input, &i): expands `$?`, `$$`, etc. (bonus).
// 	- append_and_free(char *base, char *to_append): joins and frees previous.
// 	- append_char(char *base, char c): appends one character to the string.

// 	return:
// 	- the fully expanded string, or NULL on memory error.

// 	note:
// 	- this function does not perform tokenization or quote handling.
// 	- it's called **after** quote resolution and used per token (ex: in handle_variable()).
// */

// char *expand_variable(t_data *data, char *input)
// {
// 	char	*value;
// 	char	*var_name;
// 	int		i;

// 	i = 0;
// 	value = ft_strdup("");
// 	if (!value)
// 		return (perror("Error: getting value with ft_strdup("") @ expand_variable"), NULL);
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			i++;
// 			if (input[i] == '?')
// 				value = handle_nonstandard_var(data, input, &i);
// 			else if (is_valid_var_start(input[i]))
// 			{
// 				var_name = extract_var_name(input, &i);
// 				value = get_variable_value(data, var_name);
// 				free(var_name);
// 			}
// 			else
// 				value = ft_strdup(""); // e.g. $!
// 			value = append_and_free(value, value);
// 		}
// 		else
// 		{
// 			value = append_char(value, input[i]);
// 			i++;
// 		}
// 	}
// 	return (var_name);
// }
//     // 1. Scan the string to find variable occurrences.
//     // 2. For each $, determine the variable name.
//     // 3. Get the variable's value via get_variable_value().
//     // 4. Replace variable token with value in the output string.
//     // 5. Return fully expanded string.


// /*
// 	information concerning: handle_variable

// 	purpose: expands shell variables (e.g. $USER, $?) in WORD tokens.

// 	for: echo "Hello $USER"

// 	it scans each token in the list, and if the token is of type WORD
// 	and not inside single quotes, it searches for the '$' character.

// 	- if '$' is found:
// 		- calls expand_variable() to replace it with the actual value
// 		- frees the old token value
// 		- assigns the new expanded string back to the token

// 	expansion is skipped for tokens inside single quotes (no expansion there).
// 	inside double quotes, expansion is allowed.

// 	this step is essential to resolve environment variables before
// 	building the argv array used in execve().
// 	it does not touch heredocs — that is handled separately.
// */

// void	handle_variable(t_data *data, t_token *tokens)
// {
// 	t_token	*current = tokens;
// 	char *expanded;

// 	while (current) // or current != end
// 	{
// 		if (tokens->type == WORD && tokens->quote != SINGLE_QUOTE)
// 		{
// 			if (ft_strchr(current->value, '$'))
// 			{
// 				expanded = expand_variable(data, current->value);
// 				if(!expanded)
// 					return (perror("Error: expanding variable @ handle_variable"));
// 				free (current->value); //really?
// 				current->value = expanded;
// 			}
// 		}
// 		current = current->next;
// 	}
// }




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

//	garbage
// char	*expansion_string_alloc(char *input)
// {
// 	int		length;
// 	char	*result;

// 	length = ft_strlen(input);
// 	result = malloc(sizeof(char*) * length + 1);
// 	if (!result)
// 	{
// 		free (result);
// 		printf("eror allocating memory for result @ parser_variable_handling\n");
// 		return (0);
// 	}
// }

char	*handle_exit_code(t_data *data, char *input)
{
	char	*status;
	char	*result;

	status = ft_itoa(data->last_exit_code_status);
	result = ft_strjoin(input, status);
	free (status);
	return (result);
}
char	*handle_environment_variable(const char *input, int	i, t_data *data, char * result)
{
	
}
char	*expand_variables(const char *input, t_token *tokens, t_data *data)
{
	int	i;
	char	*result;

	i = 0;
	result = strdup("");
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
			{
				result = handle_exit_code(data, input[i]);
				i++;
			}
			else if (ft_isalpha(input[i]) || input[i] == "_")
			{
				result = get_env_value(data, *input); // or token value
			}
			else
			{
				result = ft_strjoin_char(result, '$');
			}
			result[j] = result[i];
		}
		else
		{
			result = ft_strjoin_char(result, input[i]);
			i++;
		}
	}
	result[i] = '\0';
	return(result);
}

int	isexpandable_variable(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '\0')
				return (0); // $ at end, no variable
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
void	handle_variable(t_token *tokens)
{
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

