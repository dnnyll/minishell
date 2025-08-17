void	update_shlvl(t_data *data)
{
	t_env	*shlvl;
	int		level;
	char	*new_value;

	shlvl = get_shlvl_node(data);
	if (!shlvl)
		return ;
	level = ft_atoi(shlvl->value);
	if (level < 0)
		level = 0;
	else if (level > 998) // prevent huge values like Bash
		level = 999;
	else
		level++;
	new_value = ft_itoa(level);
	if (!new_value)
		return ;
	free(shlvl->value);
	shlvl->value = new_value;
}
