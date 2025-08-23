/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_handling_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:04:09 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/23 15:04:12 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extend_outfiles(t_command *cmd)
{
	char	**new_outfiles;
	int		*new_flags;
	int		i;

	new_outfiles = malloc(sizeof(char *) * (cmd->outfile_count + 2));
	new_flags = malloc(sizeof(int) * (cmd->outfile_count + 1));
	if (!new_outfiles || !new_flags)
		return (0);
	i = 0;
	while (i < cmd->outfile_count)
	{
		new_outfiles[i] = cmd->outfile[i];
		new_flags[i] = cmd->append_flags[i];
		i++;
	}
	new_outfiles[i] = NULL;
	if (cmd->outfile_count > 0)
	{
		free(cmd->outfile);
		free(cmd->append_flags);
	}
	cmd->outfile = new_outfiles;
	cmd->append_flags = new_flags;
	return (1);
}
