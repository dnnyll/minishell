/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:27:34 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 15:48:37 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter_match(char *line, char *delim)
{
	return (ft_strncmp(line, delim, ft_strlen(delim)) == 0
		&& line[ft_strlen(delim)] == '\0');
}

void	print_heredoc_warning(char *delim)
{
	write(2, "minishell: warning: here-document ", 34);
	write(2, "delimited by end-of-file (wanted `", 33);
	write(2, delim, ft_strlen(delim));
	write(2, "`)\n", 3);
}
