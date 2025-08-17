/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:30:29 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:30:31 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data_list(t_data **data_ptr)
{
	t_data	*data;

	if (!data_ptr || !*data_ptr)
		return ;
	data = *data_ptr;
	free_tokens(data);
	free_commands(data);
	free_env_list(data->env_head);
	free_char_array(data->environment_var);
	free(data);
	*data_ptr = NULL;
}
