/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:18:25 by mrosset           #+#    #+#             */
/*   Updated: 2025/07/02 10:50:26 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int	main(int argc, char **argv, char **envp) // test export and unset
// {
// 	(void)argc;
// 	(void)argv;
// 	t_data	data = init_data();
// 	data.environment = copy_environment(envp);

// 	char	*input;
// 	char	**split;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		add_history(input);
// 		split = ft_split(input, ' '); // simple split pour ce test

// 		if (!split || !split[0])
// 		{
// 			free_char_array(split);
// 			free(input);
// 			continue ;
// 		}

// 		if (ft_strncmp(split[0], "export", 6) == 0)
// 		{
// 			if (split[1] == NULL)
// 				no_args_export(&data);
// 			else
// 				export_builtin(split, &data);
// 		}
// 		else if (ft_strncmp(split[0], "unset", 5) == 0)
// 			unset_builtin(split, &data);
// 		else if (ft_strncmp(split[0], "exit", 5) == 0)
// 		{
// 			free_char_array(split);
// 			free(input);
// 			break ;
// 		}

// 		free_char_array(split);
// 		free(input);
// 	}

// 	free_char_array(data.environment);
// 	clear_history();
// 	return (0);
// }


// int	main(int argc, char **argv, char **envp) \\ tests cd, pwd and exit
// {
// 	(void)argc;
// 	(void)argv;
// 	t_data	data = init_data(); // Doit initialiser .environment, .oldpwd, etc.
// 	data.environment = copy_environment(envp);

// 	char	*input;
// 	char	**split;

// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		add_history(input);
// 		split = ft_split(input, ' ');
// 		if (!split || !split[0])
// 		{
// 			free(input);
// 			free_tab(split, -1);
// 			continue;
// 		}
// 		if (ft_strncmp(split[0], "exit", 5) == 0)
// 		{
// 			exit_builtin(split, &data);
// 			// Normalement ne retourne pas ici, sauf si exit échoue
// 		}
// 		else if (ft_strncmp(split[0], "cd", 3) == 0)
// 			cd_builtin(split, data.environment);
//		else if (ft_strncmp(split[0], "pwd", 4) == 0)
//			pwd_builtin(split);
// 		free_tab(split, -1);
// 		free(input);
// 	}
// 	free_char_array(data.environment);
// 	clear_history();
// 	return (0);
// }

/*
int	main(int argc, char **argv, char **envp) // test echo and env
{
	(void)argc;
	(void)argv;

	t_data	data = init_data(); // Initialise une structure avec data.env
	data.env = init_env(envp); // Convertit envp (char **) en t_env * (liste chaînée)

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
			free_char_array(split);
			free(input);
			continue;
		}

		if (ft_strncmp(split[0], "echo", 5) == 0)
			echo_builtin(split);
		else if (ft_strncmp(split[0], "env", 4) == 0)
			env_builtin(data.env);
		else if (ft_strncmp(split[0], "exit", 5) == 0)
		{
			free_char_array(split);
			free(input);
			break;
		}

		free_char_array(split);
		free(input);
	}

	free_env_list(data.env); // fonction à adapter si besoin
	clear_history();
	return (0);
}
*/