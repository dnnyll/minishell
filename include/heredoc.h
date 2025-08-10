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
void		heredoc_cleanup(t_heredoc *heredoc);
int			process_single_heredoc(t_command *cmd, t_data *data,
				t_heredoc *heredoc);
int			process_heredocs(t_data *data);

//	heredoc_fill.c
int			fill_heredoc(t_heredoc *heredoc, t_command *command, t_data *data);

//	heredoc_signal.c
int			manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc);
void		handle_heredoc_sigint(int sig);

#endif