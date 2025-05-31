/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosset <mrosset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:48:45 by mrosset           #+#    #+#             */
/*   Updated: 2025/05/30 12:22:05 by mrosset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_cmd
{
	char			**args; // tab for cmds
	char			*path; // path to executor
	char			*value;
	int				infile;
	int				outfile;
	t_type			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

#endif