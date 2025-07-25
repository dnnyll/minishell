#include "minishell.h"

#ifndef HEREDOC_H
# define HEREDOC_H

typedef	struct s_redir
{
	int	heredoc_count;
} t_redir;

typedef	struct s_heredoc
{
	char			*filename;
	int				fd;
	int				counter;
	pid_t			pid;
	t_redir			*redir_head;
} t_heredoc;

//	heredoc_temp.c
t_heredoc	*init_heredoc(int counter);	//removed argument: count , need info
char		*create_heredoc_filename(int id);
int			open_heredoc_filename(t_heredoc *heredoc);
int			write_line_to_heredoc(int fd, char *line);
int			fill_heredoc(t_heredoc *heredoc, t_command *command, t_data *data);
void		heredoc_cleanup(t_heredoc *heredoc);
int			launch_heredoc(t_data *data);
int	process_heredocs(t_data *data);

# endif


//	need to count how many heredocs in the parsing and store thme in heredoc struct
//	need to store all my heredoc files that were input in my heredoc struct in a int**? or char**?
//	need to check if HEREDOC then my command has to add the infile/outfile name so we can
//		execute it as a redirection! this way we dont have to handle heredoc in the execution
//		ewe can simply use redirections and append