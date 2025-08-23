/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_management.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:27:54 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/23 11:36:58 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_MANAGEMENT_H
# define ENVIRONMENT_MANAGEMENT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//	environment_default.c
t_env	*find_or_create_node(t_data *data, const char *key, const char *initial_value);
void	update_pwd_vars(t_data *data);
char	**create_default_env(void);
void 	update_pwd_vars(t_data *data);
void change_directory(t_data *data, const char *path);

//	environment_handling.c
char	**copy_environment(char **envp);
char	*search_env_value(t_data *data, const char *variable_name);
char	*handle_environment_variables(const char *input, int *i,
			t_data *data, char *result);

//	environment_parsing.c
char	*search_list_env_value(t_env *env_head, const char *name);
void	add_env_node(t_env **head, t_env *new_node);
t_env	*create_node(const char *env_var_line);
t_env	*build_env_list(char **environment_var);

//	environment_shlvl.c
t_env	*find_or_create_node(t_data *data, const char *key, const char *initial_value);
void	update_env_array(t_data *data);
void	increment_shlvl(t_env *env_head);



#endif