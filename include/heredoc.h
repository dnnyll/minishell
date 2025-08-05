
#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_heredoc
{
	char	*filename;  // Path to the temporary file
	char	*delimiter;
	int		quoted;
	int		fd;         // File descriptor opened on that file
	int		counter;    // Used for unique filename generation (e.g. heredoc_0, heredoc_1...)
	pid_t	pid;        // PID of the child that handled the heredoc input (if used)
	struct s_heredoc	*next;
}	t_heredoc;

//	heredoc_temp.c
t_heredoc	*init_heredoc(int counter);	//removed argument: count , need info
char		*create_heredoc_filename(int id);
int			open_heredoc_filename(t_heredoc *heredoc);
int			write_line_to_heredoc(int fd, char *line);
void		heredoc_cleanup(t_heredoc *heredoc);
int			process_heredocs(t_data *data);

//	heredoc_fill.c
int			fill_heredoc(t_heredoc *heredoc, t_command *command, t_data *data);

//	heredoc_signal.c
int		manage_heredoc(t_command *cmd, t_data *data, t_heredoc *heredoc);
void	handle_heredoc_sigint(int sig);

#endif