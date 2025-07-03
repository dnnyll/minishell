#include <minishell.h>


// /* ===== ENVIRONMENT VARIABLE MANAGEMENT & EXPANSION PRE-CHECKLIST ===== */

// /* 1. ENVIRONMENT COPY */
// [x] Copy envp into your own char **env (e.g. data->env)
// [x] Use strdup for each line (don’t copy pointers directly)
// [x] Make a free_env(char **env) function

// /* 2. ACCESS FUNCTION FOR LOOKUP */
// [ ] Implement get_env_value(t_data *data, const char *name)
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
| 1. Copy real environment into               |
|      → data->environment                    |
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
| 2. Else → CALL get_env_value(data, name)    |
|     - Search in data->environment           |
|     - Found? → return copy of value         |
|                                             |
| 3. Else → return NULL (empty string)        |
+---------------------------------------------+


*/


//	TIME TO CREATE MYVAR from the example $MYVAR=hello




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

char	*search_variable_value(t_data *data, const char *name)
{
	t_variiables	*current;

	if (!data || !name)
		return (perror("Error: empty data or name @ search_variable_value\n"), NULL);

	// 1. Check local user-defined vars (assignments not exported)
	current = data->local_variables;
	while (current)
	{
		if (ft_strncmp(current->key, name) == 0)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (get_env_value(data, name));
}

char	*get_env_value(t_data *data, const char *name)
{
	int	i;
	int	length;

	i = 0;
	length = ft_strlen(name);
	if (!data || !name)
		return (perror("Error: empty data or name @ get_env_value\n"), NULL);
	while(data->environment[i])
	{
		printf("Checking env[%d]: %s\n", i, data->environment[i]);
		// Compare the variable name with the beginning of the environment string
		if (ft_strncmp(data->environment[i], name, length) == 0
			&& data->environment[i][length] == '=')
			{
				printf("Match found: %s\n", data->environment[i]);
				printf("Returning value: %s\n", data->environment[i] + length + 1);
				// Return a copy of the value part (after the '=' sign)
				return (ft_strdup(data->environment[i] + length + 1));
			}
			i++;
	}
	printf("No match found for: %s\n", name);
	return(NULL); //	if not found
}
