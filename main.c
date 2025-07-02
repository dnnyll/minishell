#include "minishell.h"

int	main(int argc, char **argv, char **envp) //tests cd, pwd and exit
{
	(void)argc;
	(void)argv;
	t_data	data = init_data(); // Doit initialiser .environment, .oldpwd, etc.
	data.environment = copy_environment(envp);

	char	*input;
	char	**split;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		add_history(input);
		split = ft_split(input, ' ');
		if (!split || !split[0])
		{
			free(input);
			free_tab(split, -1);
			continue;
		}
		if (ft_strncmp(split[0], "exit", 5) == 0)
		{
			exit_builtin(split, &data);
			// Normalement ne retourne pas ici, sauf si exit échoue
		}
		else if (ft_strncmp(split[0], "cd", 3) == 0)
			cd_builtin(split, data.environment);
		else if (ft_strncmp(split[0], "pwd", 4) == 0)
			pwd_builtin(split);
		free_tab(split, -1);
		free(input);
	}
	free_char_array(data.environment);
	clear_history();
	return (0);
}