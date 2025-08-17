/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniefe2 <daniefe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 13:28:07 by daniefe2          #+#    #+#             */
/*   Updated: 2025/08/17 13:28:10 by daniefe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_heredoc
{
	char				*filename;
	char				*delimiter;
	int					index;
	int					quoted;
	int					fd;
	int					counter;
	pid_t				pid;
	struct s_heredoc	*next;
}	t_heredoc;

//	heredoc_temp.c
t_heredoc	*init_heredoc(int counter);
char		*create_heredoc_filename(int pid, int index);
int			open_heredoc_filename(t_heredoc *heredoc);
int			write_line_to_heredoc(int fd, char *line);
int			process_single_heredoc(t_command *cmd,
				t_data *data, t_heredoc *heredoc);
int			process_heredocs(t_data *data);

//	heredoc_fill.c
int			fill_heredoc(t_heredoc *heredoc, t_command *command, t_data *data);

//	heredoc_signal.c
void		unlink_filename(t_data *data);
int			manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc);

//	heredoc_utils.c
int			is_delimiter_match(char *line, char *delim);
void		print_heredoc_warning(char *delim);

#endif