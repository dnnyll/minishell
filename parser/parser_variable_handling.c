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

