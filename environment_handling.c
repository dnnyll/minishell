#include <minishell.h>


// /* ===== ENVIRONMENT VARIABLE MANAGEMENT & EXPANSION PRE-CHECKLIST ===== */

// /* 1. ENVIRONMENT COPY */
// [x] Copy envp into your own char **env (e.g. data->env)
// [x] Use strdup for each line (don’t copy pointers directly)
// [x] Make a free_env(char **env) function

// /* 2. ACCESS FUNCTION FOR LOOKUP */
// [ ] Implement search_env_value(t_data *data, const char *name)
//     - Iterate through env[]
//     - Find key before '='
//     - Return strdup of the value after '=' if match
//     - Return NULL if not found

// /* 3. SPECIAL CASE: $? */
// [ ] If token is exactly "$?", replace with ft_itoa(data->last_exit_status)

// /* 4. QUOTE HANDLING */
// [x] Track quote type per token (SINGLE_QUOTE, DOUBLE_QUOTE, NO_QUOTE)
// [ ] Skip expansion if inside SINGLE_QUOTE
// [ ] Allow expansion in DOUBLE_QUOTE and NO_QUOTE

// /* 5. MULTIPLE VARIABLES IN ONE TOKEN */
// [ ] Make sure to expand all $VARs in a string like "Path: $HOME/$USER"
//     - Loop through the string
//     - Replace each $VAR individually
//     - Build the final expanded string

// /* 6. EDGE CASES TO HANDLE */
// [ ] `$` at end of string → keep as literal `$`
// [ ] `$` followed by invalid identifier char → ignore expansion
// [ ] `$` with undefined var → replace with empty string ("")
// [ ] (Optional) Handle numeric vars like $1, $2 — if required

// /* 7. MEMORY MANAGEMENT */
// [x] Free original token->value before assigning new string
// [ ] Ensure expanded strings are malloced
// [ ] All final strings should be freed in free_tokens()

// /* 8. TEST CASES TO CHECK */
// [ ] echo $HOME
// [ ] echo "$HOME"
// [ ] echo '$HOME'
// [ ] echo $UNDEFINED_VAR
// [ ] echo $?
// [ ] echo $HOME$USER
// [ ] echo "$HOME is $USER"


/*
+---------------------------------------------+
|              minishell launch               |
|---------------------------------------------|
| 1. Copy real environment_variables into               |
|      → data->environment_variables                    |
|                                             |
| 2. Initialize local variable list           |
|      → data->local_vars = NULL              |
+---------------------------------------------+

              |
              v

+---------------------------------------------+
|         User types a command:               |
|       echo "Hello $USER $FOO"               |
+---------------------------------------------+
              |
              v

+---------------------------------------------+
|         Tokenization happens                |
| - Splits into tokens                        |
| - Keeps quotes info                         |
+---------------------------------------------+
              |
              v

+---------------------------------------------+
|       handle_variables(tokens)              |
| - If token->quote != SINGLE_QUOTE           |
| - AND contains $                            |
| → set token->expandable = 1                 |
+---------------------------------------------+
              |
              v

+---------------------------------------------+
|       Variable expansion stage              |
| For each token marked expandable:           |
|   new_str = process_variables(token->value) |
+---------------------------------------------+
              |
              v

+---------------------------------------------+
|   process_variables(value string)           |
| - Walk through string character by char     |
| - When $ is found:                          |
|     var_name = extract from string          |
|     → CALL lookup_variable(data, var_name)  |
|                                             |
|     THIS is where lookup_variable() happens |
+---------------------------------------------+
              |
              v

+---------------------------------------------+
|        lookup_variable(data, name)          |
|                                             |
| 1. Check data->local_vars (FOO, BAR, etc.)  |
|     - Found? → return copy of value         |
|                                             |
| 2. Else → CALL search_env_value(data, name)    |
|     - Search in data->environment_variables           |
|     - Found? → return copy of value         |
|                                             |
| 3. Else → return NULL (empty string)        |
+---------------------------------------------+




typedef struct s_variables
	{
		char				*key;
		char				*value;
		struct s_variables	*next;
}	t_variables;






*/

// //	DO NOT NEED TO CREATE PARSING FOR LOCAL VARIABLES: MYVAR=cake
// int	is_local_variable(char c)
// {
// 	return (c == '=');
// }

// void	identify_local_variables(t_variables *variables, t_token *tokens, char *input_variable)
// {
// 	t_token	*current_token = tokens;
// 	t_variables	*current_variables = variables;
// 	int	i;
// 	int	input_variable_length;
	
// 	i = 0;
// 	input_variable_length = ft_strlen(input_variable);
// 	while(current_token)
// 	{
// 		if (current_token == WORD)
// 		{
// 			while (current_token->value[i])
// 			{
// 				if (is_local_variable(current_token->value[i]))
// 				{
// 					char *temp = ft_substr(current_token->value, 0, i);
// 					current_variables->key = temp;
// 					free (temp);
// 					temp = ft_substr(current_token->value, i, input_variable_length);
// 					current_variables->value = temp;
// 					free(temp);
// 					return ;
// 				}
// 					else
// 						i++;
// 			}
// 		}
// 		current_token = current_token->next;
// 	}
// 	printf("s_variables\n");
// 	printf("key: %s\n | value: %s\n", current_variables->key, current_variables->value);
// }


// char	**store_local_variables(char *variable_input)
// {
// 	int	i;
// 	char	**local_variables_storage;

// 	i = 0;
// 	while(variable_input[i])
// 		i++;
// 	local_variables_storage = malloc(sizeof(char*) * (i + 1));
// 	if(!local_variables_storage)
// 		return (perror("Error: alloc local_variaibles_storage @ store_local_variables\n"), NULL);
// 	i = 0;
// 	while (variable_input[i])
// 	{
// 		local_variables_storage[i] = ft_strdup(variable_input[i]);
// 		i++;
// 	}
// 	if (!local_variables_storage)
// 		return (perror("Error: copying variable_input to loca_variables_storage @ store_local_variables\n"), NULL);
// 	return (local_variables_storage);
// }

char	**copy_environment(char **envp)
{
	int		i;
	char	**environment_copy;

	i = 0;
	while (envp[i])
		i++;
	environment_copy = malloc(sizeof(char*) * (i + 1));
	if (!environment_copy)
		return (perror("Error: arlloc environemnt_copy @ copy_environment\n"), NULL);
	i = 0;
	while (envp[i])
	{
		environment_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	if (!environment_copy)
		return (perror("Error: copying envp to environment_copy @ copy_environment\n"), NULL);
	return (environment_copy);
}


//	used to search and verify if its a local variable or a environment_variables variable
//	we still need to store the varibales in our data structure as char **local_variables
// char	*search_variable_name(t_data *data, const char *variable_name)
// {
// 	int	i;
// 	int	variable_length;

// 	if (!data || !variable_name)
// 		return (perror("Error: empty data or name @ search_variable_name\n"), NULL);
// 	i = 0;
// 	variable_length = ft_strlen(variable_name);
// 	// 1. Check local user-defined vars (assignments not exported)
// 	while (data->local_variables[i])
// 	{
// 		printf("Checking local_variables[%d]: %s\n", i, data->local_variables[i]);
// 		// Compare the variable name with the beginning of the local_variable string
// 		if (ft_strncmp(data->local_variables[i], variable_name, variable_length) == 0)
// 		{
// 			printf("Match found: %s\n", data->environment_variables[i]);
// 			printf("Returning value: %s\n", data->environment_variables[i] + variable_length + 1);
// 			// Return a copy of the value part (after the '=' sign)
// 			return (ft_strdup(data->local_variables[i] + variable_length + 1));
// 		}
// 		i++;
// 	}
// 	printf("No match found for: %s within the local_variables\n", variable_name);
// 	printf("Now seraching environment variables\n");
// 	return (search_env_value(data, variable_name));
// }
//	used to search the environemnt varibles name wihtin the copy of the environment
char	*search_env_value(t_data *data, const char *variable_name)
{
	int	i;
	int	variable_length;

	i = 0;
	variable_length = ft_strlen(variable_name);
	if (!data || !variable_name)
		return (perror("Error: empty data or name @ search_env_value\n"), NULL);
	while(data->environment_variables[i])
	{
		printf("Checking env[%d]: %s\n", i, data->environment_variables[i]);
		// Compare the variable name with the beginning of the environment_variables string
		if (ft_strncmp(data->environment_variables[i], variable_name, variable_length) == 0
			&& data->environment_variables[i][variable_length] == '=')
			{
				printf("Match found: %s\n", data->environment_variables[i]);
				printf("Returning value: %s\n", data->environment_variables[i] + variable_length + 1);
				// Return a copy of the value part (after the '=' sign)
				return (ft_strdup(data->environment_variables[i] + variable_length + 1));
			}
			i++;
	}
	printf("No match found for: %s\n", variable_name);
	return(NULL); //	if not found
}
