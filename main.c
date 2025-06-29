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
		split = ft_split(input, ' '); // simple split pour ce test

		if (!split || !split[0])
		{
			free_char_array(split);
			free(input);
			continue ;
		}

		if (ft_strncmp(split[0], "export", 6) == 0)
		{
			if (split[1] == NULL)
				no_args_export(&data);
			else
				export_builtin(split, &data);
		}
		else if (ft_strncmp(split[0], "unset", 5) == 0)
			unset_builtin(split, &data);
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