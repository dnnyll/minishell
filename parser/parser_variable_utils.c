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
		perror("alloc at ft_strjoin_char failed\n");
	while (i < len)
	{
		result[i] = input[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	return (result);
}

char	*append_char_to_result(char *result, char c, int *i)
{
	char	*temp;

	temp = ft_strjoin_char(result, c);
	free(result);
	result = temp;
	(*i)++;
	return (result);
}

int	is_expandable_variable(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '$' || str[i] == '?'
				|| ft_isalpha(str[i]) || str[i] == '_')
				return (1);
		}
		else
			i++;
	}
	return (0);
}
