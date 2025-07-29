
#ifndef ENVIRONMENT_MANAGEMENT_H
# define ENVIRONMENT_MANAGEMENT_H

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

//	environment_handling
char	**copy_environment(char **envp);
char	*search_env_value(t_data *data, const char *variable_name);

//	environment_parsing
char	*search_list_env_value(t_env *env_head, const char *name);
void	add_env_node(t_env **head, t_env *new_node);
void	free_env_list(t_env *env);
t_env	*create_node(const char *env_var_line);
t_env	*build_env_list(char **environment_var);

#endif