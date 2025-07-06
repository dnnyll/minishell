#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_data	data = init_data();
	data.environment = copy_environment(envp);

	char	*input;
	char	**split;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		split = ft_split(input, ' ');
		if (!split || !split[0])
		{
			free_char_array(split);
			free(input);
			continue ;
		}

		if (ft_strncmp(split[0], "echo", 5) == 0)
			echo_builtin(split);
		else if (ft_strncmp(split[0], "env", 4) == 0)
			env_builtin(&data);
		else if (ft_strncmp(split[0], "exit", 5) == 0)
		{
			free_char_array(split);
			free(input);
			break ;
		}

		free_char_array(split);
		free(input);
	}

	free_char_array(data.environment);
	clear_history();
	return (0);
}

