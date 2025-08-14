#include "minishell.h"

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
		perror("alloc at ft_strjoin_char failed\n");
		// free(result);
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
		(*i)++;
	variable_name = ft_substr(input, start, *i - start);
	value = search_env_value(data, variable_name);
	if (!value)
		return (printf("Error: search_env_value not found for the input\n"),
			NULL);
	free(variable_name);
	new_result = ft_strjoin(result, value);
	free(value); // might not need to be freed, check leaks
	return (new_result);
}

static char	*dollar_case(const char *input, int *i, char *result, t_data *data)
{
	char	*temp;

	(*i)++;
	if (input[*i] == '?')
	{
		temp = handle_exit_code(data, result);
		free(result);
		result = temp;
		(*i)++;
	}
	else if (ft_isalpha(input[*i]) || input[*i] == '_')
	{
		temp = handle_environment_variables(input, i, data, result);
		free(result);
		result = temp;
	}
	else
	{
		temp = ft_strjoin_char(result, '$');
		free(result);
		result = temp;
	}
	return (result);
}

static char	*char_case(char *result, char c, int *i)
{
	char *temp;

	temp = ft_strjoin_char(result, c);
	free(result);
	result = temp;
	(*i)++;
	return (result);
}

char	*expand_variables(const char *input, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = strdup("");
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
			result = dollar_case(input, &i, result, data);
		else
			result = char_case(result, input[i], &i);
	}
	return (result);
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
			if (str[i] == '$' || str[i] == '?' || ft_isalpha(str[i]) || str[i] == '_')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

//	extra note: this is a flaggin 0 or 1 either if they are or arent expandable
void	handle_variables(t_token *tokens)
{
	t_token	*current = tokens;

	while (current)
	{
		if (current->type == WORD && current->quote != SINGLE_QUOTE
			&& isexpandable_variable(current->value))
			current->expandable = 1;
		else
			current->expandable = 0;
		current = current->next;
	}
}

char	*process_variables(const char *input, t_data *data, t_token *tokens)
{
	t_token *current = tokens;
	char *expanded;

	handle_variables(current);
	expanded = expand_variables(input, data);
	return (expanded);
}


// char	*expand_variables(const char *input, t_data *data)
// {
// 	int		i;
// 	char	*result;
// 	char	*temp;

// 	i = 0;
// 	result = strdup("");
// 	if (!result)
// 	{
// 		return (NULL);
// 		free(result);
// 	}
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			i++;
// 			if (input[i] == '?')
// 			{
// 				temp = handle_exit_code(data, result);
// 				free(result);
// 				result = temp;
// 				i++;
// 			}
// 			else if (ft_isalpha(input[i]) || input[i] == '_')
// 			{
// 				temp = handle_environment_variables(input, &i, data, result);
// 				free (result);
// 				result = temp;
// 			}
// 			else
// 			{
// 				temp = ft_strjoin_char(result, '$');
// 				free (result);
// 				result = temp;
// 			}
// 		}
// 		else
// 		{
// 			temp = ft_strjoin_char(result, input[i]);
// 			free (result);
// 			result = temp;
// 			i++;
// 		}
// 	}
// 	return (result);
// }

// char	*expand_variables(const char *input, t_data *data)
// {
// 	int		i;
// 	char	*result;
// 	char	*temp;

// 	i = 0;
// 	result = strdup("");
// 	if (!result)
// 	{
// 		return (NULL);
// 		free(result);
// 	}
// 	while (input[i])
// 	{
// 		if (input[i] == '$')
// 		{
// 			i++;
// 			if (input[i] == '?')
// 			{
// 				temp = handle_exit_code(data, result);
// 				free(result);
// 				result = temp;
// 				i++;
// 			}
// 			else if (ft_isalpha(input[i]) || input[i] == '_')
// 			{
// 				temp = handle_environment_variables(input, &i, data, result);
// 				free (result);
// 				result = temp;
// 			}
// 			else
// 			{
// 				temp = ft_strjoin_char(result, '$');
// 				free (result);
// 				result = temp;
// 			}
// 		}
// 		else
// 		{
// 			temp = ft_strjoin_char(result, input[i]);
// 			free (result);
// 			result = temp;
// 			i++;
// 		}
// 	}
// 	return (result);
// }