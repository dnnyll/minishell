/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:13:53 by daniefe2          #+#    #+#             */
/*   Updated: 2025/06/08 15:31:37 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	init_data(void)	//declare in minishell.h
{
	t_data	data;

	data.command_head = NULL;
	data.command_head = NULL;
	// keep on adding whatever you need to initiatlize;

	return (data);
}