#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;

	char	*input;
	char	**split;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			break ;
		add_history(input);
		split = ft_split(input, ' ');

		if (!split || !split[0])
		{
			free_char_array(split);
			free(input);
			continue;
		}

		if (ft_strncmp(split[0], "echo", 5) == 0)
			echo_builtin(split);
		else if (ft_strncmp(split[0], "env", 4) == 0)
			env_builtin(envp);
		else if (ft_strncmp(split[0], "exit", 5) == 0)
		{
			free_char_array(split);
			free(input);
			break ;
		}

		free_char_array(split);
		free(input);
	}
	return (0);
}

