/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_variable_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 09:08:59 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/18 13:45:24 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
List of functions to implement for variable expansion:

1. char *expand_variables(t_data *data, char *input);
   - Main function that processes the input string and returns a new string
     with all variables expanded according to the rules.

2. int is_valid_var_start(char c);
   - Returns 1 if 'c' is a valid first character for a variable name (letter or '_'),
     otherwise returns 0.

3. char *extract_var_name(const char *input, int *index);
   - Starting at input[*index], extracts the variable name (consisting of letters,
     digits, and underscores) and advances *index to the character after the name.
   - Returns a newly allocated string containing the variable name.

4. char *get_variable_value(t_data *data, const char *name);
   - Looks up the value of the variable 'name' in your internal export list or the
     environment variables.
   - Returns a newly allocated string with the variable's value or an empty string
     if not found.

5. char *handle_nonstandard_var(t_data *data, const char *input, int *index);
   - Handles special variables like "$?" (exit status).
   - Advances *index appropriately.
   - Returns a newly allocated string containing the special variable's value.

6. char *append_and_free(char *result, char *addition);
   - Concatenates 'result' and 'addition' into a new string.
   - Frees 'result' and 'addition'.
   - Returns the new concatenated string.

7. char *append_char(char *result, char c);
   - Appends a single character 'c' to 'result'.
   - Frees the old 'result' and returns the new string.

Each function should focus on its specific job to keep your code modular,
easy to maintain, and test.
*/

int is_valid_var_start(char c);
// return (ft_isalpha(c) || c == '_');

char	*extract_var_name(char *variable)
{
	int	i;
	
	i = 0;
	while (variable[i] && (ft_isalnum(variable[i] || variable[i] == '_')))
		i++;
	return (ft_substr(variable, 0 , i));
	
}
char *get_variable_value(t_data *data, const char *name);

char *handle_nonstandard_var(t_data *data, const char *input, int *i);


char *expand_variable(t_data *data, char *input)
{
	char	*result;
	char	*var_name;
	int		i;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (perror("Error: getting result with ft_strdup("") @ expand_variable"), NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			i++;
			if (input[i] == '?')
				result = handle_special_var(data, input, &i);
			else if (is_valid_var_start(input[i]))
			{
				var_name = extract_var_name(input, &i);
				result = get_variable_result(data, var_name);
				free(var_name);
			}
			else
				result = ft_strdup(""); // e.g. $!
			result = append_and_free(result, result);
		}
		else
		{
			result = append_char(result, input[i]);
			i++;
		}
	}
	return (var_name);
}
    // 1. Scan the string to find variable occurrences.
    // 2. For each $, determine the variable name.
    // 3. Get the variable's result via get_variable_result().
    // 4. Replace variable token with result in the output string.
    // 5. Return fully expanded string.


/*
    get_variable_result: Helper to get the result of a single variable.

    - Takes the variable name (e.g. "PATH", "?", "HOME").
    - Checks for special variables:
      - "?" returns exit status from data->exit_status.
      - Others check environment variables or internal export list.
    - Returns the variable's result as a string or empty string if not found.
*/
char *get_variable_result(t_data *data, const char *var_name)
{
    // Handle special variables first.
    // Query environment or internal export for other variables.
    // Return newly allocated string or "" if none.
}


/*
	information concerning: handle_variable

	purpose: expands shell variables (e.g. $USER, $?) in WORD tokens.

	for: echo "Hello $USER"

	it scans each token in the list, and if the token is of type WORD
	and not inside single quotes, it searches for the '$' character.

	- if '$' is found:
		- calls expand_variable() to replace it with the actual result
		- frees the old token result
		- assigns the new expanded string back to the token

	expansion is skipped for tokens inside single quotes (no expansion there).
	inside double quotes, expansion is allowed.

	this step is essential to resolve environment variables before
	building the argv array used in execve().
	it does not touch heredocs — that is handled separately.
*/

void	handle_variable(t_data *data, t_token *tokens)
{
	t_token	*current = tokens;
	char *expanded;

	while (current) // or current != end
	{
		if (tokens->type == WORD && tokens->quote != SINGLE_QUOTE)
		{
			if (ft_strchr(current->result, '$'))
			{
				expanded = expand_variable(data, current->result);
				if(!expanded)
					return (perror("Error: expanding variable @ handle_variable"));
				free (current->result); //really?
				current->result = expanded;
			}
		}
		current = current->next;
	}
}

